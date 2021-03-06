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
 * */

#ifndef AGENT_FRAMEWORK_COMMAND_STORAGE_JSON_GET_COMPONENT_COLLECTION_HPP
#define AGENT_FRAMEWORK_COMMAND_STORAGE_JSON_GET_COMPONENT_COLLECTION_HPP

#include "agent-framework/command/command_json.hpp"
#include "agent-framework/command/storage/get_component_collection.hpp"

namespace agent_framework {
namespace command{
namespace storage {
namespace json {

using agent_framework::command::CommandJson;

class GetComponentCollection : public CommandJson {
    Json::Value m_add_component(
        storage::GetComponentCollection::Response::Component& component);
    Json::Value m_add_components(
        std::vector<storage::GetComponentCollection::Response::Component>& components);
public:
    static constexpr const char* AGENT = storage::GetComponentCollection::AGENT;
    static constexpr const char* TAG = storage::GetComponentCollection::TAG;

    GetComponentCollection();

    void method(const Json::Value& params, Json::Value& result) final override;

    void notification(const Json::Value& params) final override;
};

}
}
}
}

#endif /*! AGENT_FRAMEWORK_COMMAND_STORAGE_JSON_GET_COMPONENT_COLLECTION_HPP */
