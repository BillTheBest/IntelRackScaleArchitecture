/**
 * Copyright (c)  2015, Intel Corporation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <errno.h>

#include "libjson/json.h"
#include "libjsonrpc/jsonrpc.h"
#include "libassetd/assetd_type.h"
#include "libjsonrpcapi/assetd_socket.h"
#include "libutils/sock.h"
#include "libutils/dump.h"
#include "libmemdb/memdb.h"
#include "librmmlog/rmmlog.h"
#include "librmmcfg/rmm_cfg.h"
#include "libjsonrpc/jsonrpc.h"
#include "libredfish/rf_event.h"
#include "libjsonrpcapi/libjsonrpcapi.h"
#include "libjsonrpcapi/parser.h"
#include "libutils/rmm.h"
#include "libutils/string.h"
#include "libassetd/assetd_jrpc_def.h"

static int add_reg_info(char *name, int64 ip_addr, int64 port, gami_cap_t *cap, json_t *resp)
{
	int i = 0;
	int nodenum = 0;
	char query[MAX_NAME_LEN] = {0};
	char buff[512] = {0};
	char ip_str[64] = {0};
	memdb_integer module_node_id = 0;
	memdb_integer reg_node_id = 0;
	struct node_info *subnode = NULL;
	int rc = 0;

	subnode = libdb_list_subnode_by_type(DB_RMM, MC_TYPE_RMC, MC_TYPE_REG, &nodenum, NULL, LOCK_ID_NULL);
	if (nodenum > 1) {
		rmm_log(ERROR, "reg node number is not right\n");
		return -1;
	}

	if (nodenum == 0)
		reg_node_id = libdb_create_node(DB_RMM, MC_TYPE_RMC, MC_TYPE_REG, SNAPSHOT_NEED, LOCK_ID_NULL);
	else
		reg_node_id = subnode[0].node_id;

	subnode = libdb_list_subnode_by_type(DB_RMM, reg_node_id, MC_TYPE_REG_MODULE, &nodenum, NULL, LOCK_ID_NULL);
	for (i = 0; i < nodenum; i++) {
		libdb_attr_get_string(DB_RMM, subnode[i].node_id, JRPC_GAMI_REG_NAME, query, MAX_NAME_LEN, LOCK_ID_NULL);
		if (strcmp(query, name) == 0)
			break;
	}

	if (nodenum == i) {
		module_node_id = libdb_create_node(DB_RMM, reg_node_id, MC_TYPE_REG_MODULE, SNAPSHOT_NEED_NOT, LOCK_ID_NULL);
		rc = libdb_attr_set_string(DB_RMM, module_node_id, JRPC_GAMI_REG_NAME, 0, name, SNAPSHOT_NEED_NOT, LOCK_ID_NULL);
		if (rc == -1) {
			rmm_log(ERROR, "memdb set reg name fail\n");
			return -1;
		}
	} else
		module_node_id = subnode[i].node_id;

	snprintf(ip_str, sizeof(ip_str), "%llu.%llu.%llu.%llu", ip_addr&0xff, (ip_addr>>8)&0xff, (ip_addr>>16)&0xff, (ip_addr>>24)&0xff);
	rc = libdb_attr_set_string(DB_RMM, module_node_id, JRPC_GAMI_REG_IP, 0, ip_str, SNAPSHOT_NEED_NOT, LOCK_ID_NULL);
	if (rc == -1) {
		rmm_log(ERROR, "memdb set reg ip fail\n");
		return -1;
	}
	rc = libdb_attr_set_int(DB_RMM, module_node_id, JRPC_GAMI_REG_PORT, 0, port, SNAPSHOT_NEED_NOT, LOCK_ID_NULL);
	if (rc == -1) {
		rmm_log(ERROR, "memdb set reg port fail\n");
		return -1;
	}

	/*mbp*/
	for (i = 0; i < GAMI_MAX_CAP_NUM; i++) {
		if ((strlen(cap->cap_mbp[i]) != 0) && (strlen(cap->cap_mbp[i]) < GAMI_MAX_NAME_LEN)) {
			strncpy_safe(buff + strlen(buff), cap->cap_mbp[i], sizeof(buff) - strlen(buff), strlen(cap->cap_mbp[i]));
			strncpy_safe(buff + strlen(buff), GAMI_CAP_SPLIT_STR, sizeof(buff) - strlen(buff), strlen(GAMI_CAP_SPLIT_STR));
		}
	}
	rc = libdb_attr_set_string(DB_RMM, module_node_id, JRPC_GAMI_REG_CAP_MBP, 0, buff, SNAPSHOT_NEED_NOT, LOCK_ID_NULL);
	if (rc == -1) {
		rmm_log(ERROR, "memdb set mbp reg cap fail\n");
		return -1;
	}

	/*psu*/
	memset(buff, 0, 512);
	for (i = 0; i < GAMI_MAX_CAP_NUM; i++) {
		if ((strlen(cap->cap_psu[i]) != 0) && (strlen(cap->cap_psu[i]) < GAMI_MAX_NAME_LEN)) {
			strncpy_safe(buff + strlen(buff), cap->cap_psu[i], sizeof(buff) - strlen(buff), strlen(cap->cap_psu[i]));
			strncpy_safe(buff + strlen(buff), GAMI_CAP_SPLIT_STR, sizeof(buff) - strlen(buff), strlen(GAMI_CAP_SPLIT_STR));
		}
	}
	rc = libdb_attr_set_string(DB_RMM, module_node_id, JRPC_GAMI_REG_CAP_PSU, 0, buff, SNAPSHOT_NEED_NOT, LOCK_ID_NULL);
	if (rc == -1) {
		rmm_log(ERROR, "memdb set psu reg cap fail\n");
		return -1;
	}

	/*fan*/
	memset(buff, 0, 512);
	for (i = 0; i < GAMI_MAX_CAP_NUM; i++) {
		if ((strlen(cap->cap_fan[i]) != 0) && (strlen(cap->cap_fan[i]) < GAMI_MAX_NAME_LEN)) {
			strncpy_safe(buff + strlen(buff), cap->cap_fan[i], sizeof(buff) - strlen(buff), strlen(cap->cap_fan[i]));
			strncpy_safe(buff + strlen(buff), GAMI_CAP_SPLIT_STR, sizeof(buff) - strlen(buff), strlen(GAMI_CAP_SPLIT_STR));
		}
	}
	rc = libdb_attr_set_string(DB_RMM, module_node_id, JRPC_GAMI_REG_CAP_FAN, 0, buff, SNAPSHOT_NEED_NOT, LOCK_ID_NULL);
	if (rc == -1) {
		rmm_log(ERROR, "memdb set fan reg cap fail\n");
		return -1;
	}

	/*drawer*/
	memset(buff, 0, 512);
	for (i = 0; i < GAMI_MAX_CAP_NUM; i++) {
		if ((strlen(cap->cap_drawer[i]) != 0) && (strlen(cap->cap_drawer[i]) < GAMI_MAX_NAME_LEN)) {
			strncpy_safe(buff + strlen(buff), cap->cap_drawer[i], sizeof(buff) - strlen(buff), strlen(cap->cap_drawer[i]));
			strncpy_safe(buff + strlen(buff), GAMI_CAP_SPLIT_STR, sizeof(buff) - strlen(buff), strlen(GAMI_CAP_SPLIT_STR));
		}
	}
	libdb_attr_set_string(DB_RMM, module_node_id, JRPC_GAMI_REG_CAP_DRAWER, 0, buff, SNAPSHOT_NEED_NOT, LOCK_ID_NULL);

	return 0;
}

static int add_cap_array(json_t *result, char *cap_str)
{
	json_t *cap_array = NULL;
	json_t *cap = NULL;
	char tmp[256] = {0};
	const char *split = GAMI_CAP_SPLIT_STR;
	char *caps[GAMI_MAX_CAP_NUM];
	char *p;
	int i = 0, j = 0;

	strncpy_safe(tmp, cap_str, sizeof(tmp), sizeof(tmp) - 1);
	p = strtok(tmp, split);
	while (p != NULL) {
		caps[i] = strdup(p);
		p = strtok(NULL, split);
		i++;
	}

	cap_array = json_array();
	for (j = 0; j < i; j++) {
		cap = NULL;
		cap = json_object();
		add_json_string(cap, JRPC_GAMI_CAP_NAME, (unsigned char *)caps[j]);
		json_array_add(cap_array, cap);
	}

	json_array_add(result, cap_array);

	return i;

}

int process_reg_query(jrpc_req_pkg_t *req, json_t *resp)
{
	int i = 0;
	int nodenum = 0;
	char name[MAX_NAME_LEN] = {0};
	char ip_addr[MAX_NAME_LEN] = {0};
	char cap_str[GAMI_MAX_CAP_STR_LEN] = {0};
	int port = 0;
	struct node_info *subnode = NULL;
	json_t *member = NULL;

	subnode = libdb_list_subnode_by_type(DB_RMM, MC_TYPE_RMC, MC_TYPE_REG_MODULE, &nodenum, NULL, LOCK_ID_NULL);
	resp = NULL;
	resp = json_array();

	for (i = 0; i < nodenum; i++) {
		member = NULL;
		member = json_object();
		if (member != NULL) {
			libdb_attr_get_int(DB_RMM, subnode[i].node_id, JRPC_GAMI_REG_PORT, &port, LOCK_ID_NULL);
			libdb_attr_get_string(DB_RMM, subnode[i].node_id, JRPC_GAMI_REG_IP, ip_addr, MAX_NAME_LEN, LOCK_ID_NULL);
			libdb_attr_get_string(DB_RMM, subnode[i].node_id, JRPC_GAMI_REG_NAME, name, MAX_NAME_LEN, LOCK_ID_NULL);
			add_json_integer(member, JRPC_GAMI_REG_PORT, port);
			add_json_string(member, JRPC_GAMI_REG_IP, (unsigned char *)ip_addr);
			add_json_string(member, JRPC_GAMI_REG_NAME, (unsigned char *)name);
			add_cap_array(member, cap_str);
			json_array_add(resp, member);
		}
	}

	return 0;
}

static int process_gami_register(jrpc_req_pkg_t *req, json_t *resp)
{
	int64 port = 0;
	int64 ip_addr = 0;
	char *name = NULL;
	json_t *cap_array = NULL;
	json_t *cap = NULL;
	json_t *obj = NULL;
	int array_size = 0;
	int index = 0;
	char *data = NULL;
	gami_cap_t capability = { { { 0 } } };

	jrpc_get_named_param_value(req->json, JRPC_GAMI_REG_NAME, JSON_STRING, &name);
	if (name == NULL)
		return -1;
	rmm_log(DBG, "%s name: %s\n", __func__, name);

	jrpc_get_named_param_value(req->json, JRPC_GAMI_REG_IP, JSON_INTEGER, &ip_addr);
	if (ip_addr == 0)
		return -1;
	rmm_log(DBG, "%s ip_addr: %lld\n", __func__, ip_addr);

	jrpc_get_named_param_value(req->json, JRPC_GAMI_REG_PORT, JSON_INTEGER, &port);
	if (port == 0)
		return -1;
	rmm_log(DBG, "%s port: %lld\n", __func__, port);

	/*mbp*/
	jrpc_get_named_param_value(req->json, JRPC_GAMI_REG_CAP_MBP, JSON_ARRAY, (void *)&cap_array);
	if (cap_array == NULL)
		return -1;

	array_size = json_array_size(cap_array);
	for (index = 0; index < array_size; index++) {
		cap = json_array_get(cap_array, index);

		if (cap)
			obj = json_object_get(cap, JRPC_GAMI_CAP_NAME);

		if (obj)
			data = json_string_value(obj);

		if(data)
			strncpy_safe(capability.cap_mbp[index], data, GAMI_MAX_NAME_LEN, GAMI_MAX_NAME_LEN - 1);
	}

	/*psu*/
	cap_array = NULL;
	data = NULL;
	jrpc_get_named_param_value(req->json, JRPC_GAMI_REG_CAP_PSU, JSON_ARRAY, (void *)&cap_array);
	if (cap_array == NULL)
		return -1;

	array_size = json_array_size(cap_array);
	for (index = 0; index < array_size; index++) {
		cap = json_array_get(cap_array, index);

		if (cap)
			obj = json_object_get(cap, JRPC_GAMI_CAP_NAME);

		if (obj)
			data = json_string_value(obj);

		if(data)
			strncpy_safe(capability.cap_psu[index], data, GAMI_MAX_NAME_LEN, GAMI_MAX_NAME_LEN - 1);
	}

	/*fan*/
	cap_array = NULL;
	data = NULL;
	jrpc_get_named_param_value(req->json, JRPC_GAMI_REG_CAP_FAN, JSON_ARRAY, (void *)&cap_array);
	if (cap_array == NULL)
		return -1;

	array_size = json_array_size(cap_array);
	for (index = 0; index < array_size; index++) {
		cap = json_array_get(cap_array, index);

		if (cap)
			obj = json_object_get(cap, JRPC_GAMI_CAP_NAME);

		if (obj)
			data = json_string_value(obj);

		if(data)
			strncpy_safe(capability.cap_fan[index], data, GAMI_MAX_NAME_LEN, GAMI_MAX_NAME_LEN - 1);
	}

	/*drawer*/
	cap_array = NULL;
	data = NULL;
	jrpc_get_named_param_value(req->json, JRPC_GAMI_REG_CAP_DRAWER, JSON_ARRAY, (void *)&cap_array);
	if (cap_array == NULL)
		return -1;

	array_size = json_array_size(cap_array);
	for (index = 0; index < array_size; index++) {
		cap = json_array_get(cap_array, index);

		if (cap)
			obj = json_object_get(cap, JRPC_GAMI_CAP_NAME);

		if (obj)
			data = json_string_value(obj);

		if(data)
			strncpy_safe(capability.cap_drawer[index], data, GAMI_MAX_NAME_LEN, GAMI_MAX_NAME_LEN - 1);
	}

	add_reg_info(name, ip_addr, port, &capability, resp);

	return 0;
}


static int register_process_req(jrpc_req_pkg_t *req, json_t *rsp, int func_id)
{
	if (func_id == REG_APP) {
		process_gami_register(req, rsp);
	}
	return 0;
}

static void sigterm_handler(int signum)
{
	/* do cleanup jobs here */
	exit(0);
}

int main(int argc, char **argv)
{
	int ret_code;
	int fd;
	int port;
	fd_set fds;
	struct sockaddr_in addr;
	socklen_t addrlen = sizeof(addr);
	jrpc_req_pkg_t req;
	json_t *rsp = NULL;
	int func_id = 0;
	char cmd_string[JSONRPC_MAX_STRING_LEN] = {0};

	reg_sigterm_handler(sigterm_handler);

	libdb_init();
	rmm_log_init();
	enable_core_dump();

	rmm_log(INFO, "registerd daemon is Running ...\n");
	port = rmm_cfg_get_port(REGISTERD_PORT);
	if (port == 0) {
		rmm_log(ERROR, "Fail to call port.\n");
		exit(-1);
	}
	fd = create_udp_listen(INADDR_LOOPBACK, port, 0, 0);
	if (fd < 0) {
		rmm_log(ERROR, "create udp on port %d error: %s\n", port, strerror(errno));
		exit(-1);
	}

	port  = rmm_cfg_get_port(REGISTERD_JSONRPC_PORT);
	libjsonrpcapi_init(JSONRPCINIT_MEMDB | JSONRPCINIT_JIPMI, port);

	char *rsp_str = malloc(JSONRPC_MAX_STRING_LEN);
	if (rsp_str == NULL)
		return -1;

	for (;;) {
		FD_ZERO(&fds);
		FD_SET(fd, &fds);

		rsp = json_object();	/* rsp is freed in jrpc_create_result_rsp_string */

		ret_code = select(fd + 1, &fds, NULL, NULL, NULL);
		if (ret_code < 0) {
			json_free(rsp);
			continue;
		}

		ret_code = recvfrom(fd, cmd_string, sizeof(cmd_string), 0, (struct sockaddr *)&addr, &addrlen);

		parse_req(cmd_string, &req, &func_id);
		ret_code = register_process_req(&req, rsp, func_id);

		memset(rsp_str, 0, JSONRPC_MAX_STRING_LEN);
		ret_code = jrpc_create_result_rsp_string(req.id, JSONRPC_ID_TYPE_NORMAL, rsp, JSON_OBJECT, rsp_str);
		if (ret_code < 0) {
			rmm_log(ERROR, "create jrpc rsp failed\n");
			continue;
		}

		ret_code = sendto(fd, rsp_str, strlen(rsp_str)+1, 0, (struct sockaddr *)&addr, addrlen);
		if (ret_code < 0)
			rmm_log(ERROR, "socked failed: %s\n", strerror(errno));
	}

	free(rsp_str);

	close(fd);
	return 0;
}
