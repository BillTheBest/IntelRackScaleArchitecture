/*!
 * @section LICENSE
 *
 * @copyright
 * Copyright (c) 2015 Intel Corporation
 *
 * @copyright
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * @copyright
 *    http://www.apache.org/licenses/LICENSE-2.0
 *
 * @copyright
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *
 * @section DESCRIPTION
 *
 * @file command/network/json/delete_port_vlan.cpp
 *
 * @brief JSON command DeletePortVlan implementation
 * */

#include "delete_port_vlan.hpp"
#include "agent-framework/command/network/delete_port_vlan.hpp"
#include "uuid++.hh"

using namespace agent_framework::command;
using namespace agent_framework::command::network::json;

DeletePortVlan::DeletePortVlan() :
    CommandJson(Procedure(TAG,
                jsonrpc::PARAMS_BY_NAME,
                jsonrpc::JSON_OBJECT,
                "component", jsonrpc::JSON_STRING,
                "portIdentifier", jsonrpc::JSON_STRING,
                "vlanIdentifier", jsonrpc::JSON_STRING,
                "oem", jsonrpc::JSON_OBJECT,
                nullptr)) { }

void DeletePortVlan::method(const Json::Value& params, Json::Value& result) {
    try {
        Command* command = get_command();

        network::DeletePortVlan::Request request{};
        network::DeletePortVlan::Response response{};

        request.m_component = params["component"].asString();
        request.m_vlan_identifier = params["vlanIdentifier"].asString();
        request.m_port_identifier = params["portIdentifier"].asString();
        uuid id(request.m_component.c_str());

        command->execute(request, response);

        result["oem"] = response.m_oem_data.to_json();

    } catch (const command::exception::NotFound&) {
        /* @TODO: Move common exceptions to JSON command server */
        throw jsonrpc::JsonRpcException(-32602, "Component not found");
    } catch (const uuid_error_t&) {
        throw jsonrpc::JsonRpcException(-32602, "Invalid UUID format");
    } catch (...) {
        throw jsonrpc::JsonRpcException(-1, "JSON command error");
    }
}

void DeletePortVlan::notification(const Json::Value&) { }

static CommandJson::Register<DeletePortVlan> g;
