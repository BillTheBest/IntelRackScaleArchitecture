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

#include "agent-framework/command/compute/get_module_info.hpp"
#include "json/get_module_info.hpp"
#include "gtest/gtest.h"
#include "gmock/gmock.h"

using namespace agent_framework::command;
using namespace agent_framework::command::exception;

class GetModuleInfo : public compute::GetModuleInfo {
private:
    std::string m_component{};
public:
    GetModuleInfo(const std::string& component) { m_component = component; }

    using compute::GetModuleInfo::execute;

    void execute(const Request& request, Response& response) {
        auto uuid = request.get_component();

        if (uuid != m_component) {
            throw exception::NotFound();
        }

        response.set_status(agent_framework::generic::Status("TestState", "TestHealth"));
        response.set_blade_count(8);
        response.set_switch_count(8);
        response.set_fru_info(agent_framework::generic::FruInfo(
          "TestSerialNumber", "TestManufacturer", "TestModelNumber", "TestPartNumber"));
        response.set_oem(agent_framework::generic::OEMData());
    }

    virtual ~GetModuleInfo();
};

GetModuleInfo::~GetModuleInfo() { }

class GetModuleInfoTest : public ::testing::Test {
public:
    virtual ~GetModuleInfoTest();
};

GetModuleInfoTest::~GetModuleInfoTest() { }

TEST_F(GetModuleInfoTest, PositiveExecute) {
    compute::json::GetModuleInfo command_json;
    GetModuleInfo* command = new GetModuleInfo("TestModuleId");

    EXPECT_NO_THROW(command_json.set_command(command));

    Json::Value params;
    Json::Value result;

    params["component"] = "TestModuleId";

    EXPECT_NO_THROW(command_json.method(params, result));

    ASSERT_TRUE(result.isObject());
    ASSERT_TRUE(result["status"].isObject());
    ASSERT_TRUE(result["status"]["state"].isString());
    ASSERT_TRUE(result["status"]["health"].isString());
    ASSERT_TRUE(result["bladeCount"].isUInt());
    ASSERT_TRUE(result["switchCount"].isUInt());
    ASSERT_TRUE(result["fruInfo"].isObject());
    ASSERT_TRUE(result["fruInfo"]["serialNumber"].isString());
    ASSERT_TRUE(result["fruInfo"]["manufacturer"].isString());
    ASSERT_TRUE(result["fruInfo"]["modelNumber"].isString());
    ASSERT_TRUE(result["fruInfo"]["partNumber"].isString());
    ASSERT_TRUE(result["oem"].isObject());
    ASSERT_EQ(result["status"]["state"], "TestState");
    ASSERT_EQ(result["status"]["health"], "TestHealth");
    ASSERT_EQ(result["bladeCount"].asUInt(), 8);
    ASSERT_EQ(result["switchCount"].asUInt(), 8);
    ASSERT_EQ(result["fruInfo"]["serialNumber"], "TestSerialNumber");
    ASSERT_EQ(result["fruInfo"]["manufacturer"], "TestManufacturer");
    ASSERT_EQ(result["fruInfo"]["modelNumber"], "TestModelNumber");
    ASSERT_EQ(result["fruInfo"]["partNumber"], "TestPartNumber");
}

TEST_F(GetModuleInfoTest, NegativeModuleNotFound) {
    compute::json::GetModuleInfo command_json;
    GetModuleInfo* command = new GetModuleInfo("TestModuleId");

    EXPECT_NO_THROW(command_json.set_command(command));

    Json::Value params;
    Json::Value result;

    params["component"] = "OtherTestModuleId";

    EXPECT_THROW(command_json.method(params, result), jsonrpc::JsonRpcException);
}
