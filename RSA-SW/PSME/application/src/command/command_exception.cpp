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
 * @file command_exception.cpp
 *
 * @brief Command exception implementation
 * */

#include "command_exception.hpp"

using namespace psme::command::exception;

const char* Exception::what() const noexcept {
    return m_what_message;
}

Exception::~Exception() { }

NotImplemented::NotImplemented() : Exception("Not Implemented") { }
NotImplemented::~NotImplemented() { }

NotFound::NotFound() : Exception("Not Found") { }
NotFound::~NotFound() { }

InvalidCommand::InvalidCommand() : Exception("Invalid Command") { }
InvalidCommand::~InvalidCommand() { }

OverrideCommand::OverrideCommand() : Exception("Ovveride Command") { }
OverrideCommand::~OverrideCommand() { }

InvalidArgument::InvalidArgument() : Exception("Invalid Argument") { }
InvalidArgument::~InvalidArgument() { }
