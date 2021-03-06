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


#ifndef __LIBUTILS_RACK_H__
#define __LIBUTILS_RACK_H__

#include <time.h>

static inline unsigned int ZONE_ID(unsigned int addr)
{
	return (addr >> 16) & 0xFF;
}

static inline unsigned int TRAY_ID(unsigned int addr)
{
	return (addr >> 8) & 0xFF;
}

static inline unsigned int NODE_ID(unsigned int addr)
{
	return (addr) & 0xFF;
}

static inline unsigned int NODE_ADDR(unsigned int zoneId,
			unsigned int trayId, unsigned int nodeId)
{
	return ((zoneId & 0xFF) << 16) |
	       ((trayId & 0xFF) <<  8) |
	       ((nodeId & 0xFF));
}

static inline unsigned int MC_NODE_ADDR(unsigned char ipmb)
{
	ipmb = ipmb >> 1;	/* Remove 'R/W' bit, please refer to BMC code. */

	return NODE_ADDR((ipmb >> 5) & 0x03,
	                 (ipmb >> 2) & 0x07,
	                 (ipmb & 0x03));
}

static inline unsigned char MC_NODE_HEIGHT(unsigned char usize)
{
	return (usize >> 4) & 0x0F;
}

static inline unsigned char MC_NODE_WIDTH(unsigned char usize)
{
	return (usize) & 0x0F;
}

static inline unsigned char MC_NODE_SIZE(unsigned char height, unsigned char width)
{
	return ((height & 0x0F) << 4) | ((width & 0x0F));
}


#define HARD_CODE_FLAG             "==" 
#define FACTORY_DEFAULT_FLAG       "/var/memdb/factory_default"

#define BILLION     1000000000

/* MemDB related name */
#define MBP_IPV4_ADDR             "mbp_ipv4_addr"
#define TMC_SLOT_ID               "tmc_slot_id"

#define CHASSIS_TEMP_STR           "aggregated_thermal"
#define FAN_PWM_STR                "aggregated_pwm"
#define PSU_PIN_PREFIX_STR         "psu_powerin"
//#define AMON_PSU_IOUT_PREFIX_STR        "psu_currentout"
//#define AMON_FAN_PRESENT_STR            "fan_present"
//#define AMON_PSU_PRESENT_STR            "psu_present"
#define DRAWER_PRESENT_STR         "drawer_present"
#define PZONE_PRESENT_STR          "pzone_present"
#define DEVICE_ID_STR              "device_id"
#define ALERT_STR                  "amon_alert"
#define INLET_TEMP_STR             "inlet_temp"
#define UNITS                      "units"
#define X_LOC                      "x_location"
#define U_LOC                      "u_location"
#define U_HEIGHT                   "u_height"

#define TZ_PRESENT_TEMP                 "tz_present_temperature"
#define TZ_OUTLET_TEMP                  "tz_outlet_temperature"
#define TZ_VOLUM_AIRFLOW                "tz_volumetric_airflow"
#define TZ_MAX_FAN_SUP                  "tz_max_fan_support"

#define SELECT_TIME_OUT_IN_MSECONDS     100
#define CM_RUN_PERIOD_IN_MSECONDS       1000

#define SERIAL_OPEN_TIMEOUT_MS          300
#define GET_DEV_ID_TIMEOUT_MS           300
#define GET_LAN_CFG_TIMEOUT_MS          300
#define GET_CHASSIS_PRESENT_TIMEOUT_MS  1000
#define GET_FAN_PRESENT_TIMEOUT_MS      1000
#define GET_SHELF_PRESENT_TIMEOUT_MS    1000
#define GET_PSU_PRESENT_TIMEOUT_MS      1000
#define GET_ASSET_PRESENT_TIMEOUT_MS    1000
#define GET_ALERT_TIMEOUT_MS            100
#define GET_CHASSIS_TEMP_TIMEOUT_MS     (500*8)

#define MAX_FN_NUM               32
#define MAX_NAME_LEN             64
#define MAX_NODE_NUM             8
#define INVALID_NODE_ID          0x00
#define INVALID_FD               -1

#define CM_STATE_STR                  "cm_state"
#define CM_STATUS_STR                 "cm_status"
#define CM_SERIAL_PORT_NAME_STR       "serial_port"
#define CM_SERIAL_PORT_1_STR          "/dev/ttyACM0"
#define CM_SERIAL_PORT_2_STR          "/dev/ttyACM2"
#define CM_SERIAL_PORT_3_STR          "/dev/ttyACM4"


#define MC_HOTSWAP                "hotswap_status"
#define MC_IPV4_ADDR              "ipv4_addr"
#define MC_IPMB_ADDR              "ipmb_addr"
#define MC_IPMB_PROXY             "ipmb_proxy"
#define MC_U_SIZE                 "u_size"

#define PSU_TOTAL_POWER           "total_power"
#define PSU_CURRENT_POWER         "current_power"
#define PSU_NODEPOWER_PREFIX      "node_power"
#define PSU_HOSTSTATE_PREFIX      "host_state"
#define PSU_HOSTSTATE_ON          "on"
#define PSU_HOSTSTATE_OFF         "off"
#define PSU_SUPPORTPOLICY_PREFIX  "support_policy"
#define PSU_CURRENTPOLICY         "current_policy"


enum mc_type_enum {
	MC_TYPE_RMC = 0x00,
	MC_TYPE_CM,
	MC_TYPE_DZONE,
	MC_TYPE_DRAWER,
	MC_TYPE_BMC,
	MC_TYPE_PZONE,
	MC_TYPE_PSU,
	MC_TYPE_TZONE,
	MC_TYPE_FAN,
	MC_TYPE_SENSOR,
	
	MC_TYPE_REG,
	MC_TYPE_REG_MODULE,

	MC_TYPE_SSA,
	MC_TYPE_SSA_MODULE,

	MC_REDFISH,
	MC_REDFISH_EVENT,
	MC_REDFISH_LOG,
	MC_REDFISH_RACK ,
	MC_REDFISH_PZONE,
	MC_REDFISH_PSU_COLL,
	
	MC_REDFISH_TZONE,
	MC_REDFISH_FAN_COLL,
	MC_REDFISH_DZONE,
	MC_REDFISH_DRAWER_COLL,
	MC_REDFISH_MZONE,
	MC_REDFISH_MBP_COLL,

	MC_REDFISH_CHANGE,
	MC_REDFISH_UPDATE,
	MC_REDFISH_ADD,
	MC_REDFISH_REMOVE,
	MC_REDFISH_ALERT,
	MC_REDFISH_LISTENER,

	MC_REDFISH_PSU,
	MC_REDFISH_FAN,
	MC_REDFISH_SYS,
	MC_REDFISH_MBP,
	MC_TYPE_END
};

#define MC_TYPE_MAX_STR_LEN 25
#define MC_NODE_ROOT 0
static char * mc_type_str[MC_TYPE_END+1] = {
	"RMC",
	"CM",
	"DZONE",
	"DRAWER",
	"BMC",
	"PZONE",
	"PSU",
	"TZONE",
	"FAN",
	"SENSOR",

	"REG",
	"REG_MODULE",

	"SSA",
	"SSA_MODULE",

	"RF",
	"RF_EVENT",
	"RF_LOG",
	"RF_RACK",
	"RF_PZONE",
	"RF_PSU_COLL",

	"RF_TZONE",
	"RF_FAN_COLL",
	"RF_DZONE",
	"RF_DRAWER_COLL",
	"RF_MZONE",
	"RF_MBP_COLL",

	"RF_CHANGE",
	"RF_UPDATE",
	"RF_ADD",
	"RF_REMOVE",
	"RF_ALERT",
	"RF_LISTENER",

	"RF_PSU",
	"RF_FAN",
	"RF_SYS",
	"RF_MBP",
	"MC_TYPE_END"
};

#endif
