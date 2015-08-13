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

#include "storage_controller_info_dto.hpp"

using namespace psme::core::dto::compute;

StorageControllerInfoDTO::~StorageControllerInfoDTO(){}

StorageControllerInfoDTO::Request::~Request(){}

StorageControllerInfoDTO::Response::~Response(){}

const Json::Value StorageControllerInfoDTO::Request::to_json() const {
    Json::Value json_request;

    json_request["component"] = get_component();
    json_request["controller"] = get_controller();

    return json_request;
}

void StorageControllerInfoDTO::Response::to_object(const Json::Value& response) {
    if (response.isObject()) {
        set_interface(response["interface"].asString());
        set_drive_count(response["driveCount"].asUInt());

        m_status.to_object(response["status"]);
        m_fru_info.to_object(response["fruInfo"]);
        m_oem_data.to_object(response["oem"]);
    }
}
