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
 * */

#include "delete_port_vlan_dto.hpp"

using namespace psme::core::dto::network;

DeletePortVlanDTO::~DeletePortVlanDTO(){}

DeletePortVlanDTO::Request::~Request(){}

DeletePortVlanDTO::Response::~Response(){}

const Json::Value DeletePortVlanDTO::Request::to_json() const {
    Json::Value json_request;
    json_request["component"] = get_component();
    json_request["portIdentifier"] = get_port_identifier();
    json_request["vlanIdentifier"] = get_vlan_identifier();
    json_request["oem"] = get_oem().to_json();
    return json_request;
}

void DeletePortVlanDTO::Response::to_object(const Json::Value& response) {
    if (response.isObject()) {
        m_oem.to_object(response["oem"]);
    }
}
