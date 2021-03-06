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
 * @file schema_reader.hpp
 *
 * @brief SchemaReader interface
 * */

#ifndef CONFIGURATION_SCHEMA_READER_HPP
#define CONFIGURATION_SCHEMA_READER_HPP

#include <memory>

namespace json { class Value; }

namespace configuration {

class SchemaValidator;

/*! JSON schema reader class */
class SchemaReader {
public:
    /*! SchemaReader constructor */
    explicit SchemaReader();
    ~SchemaReader();

    /*!
     * @brief Load JSON schema, add read property to validator
     * @param schema Schema JSON object
     * @param validator SchemaValidator object
     *
     * @return On success true is returned, otherwise false
     */
    bool load_schema(const json::Value& schema, SchemaValidator& validator);

private:
    /*! pimpl idiom */
    class Impl;
    std::unique_ptr<Impl> m_impl;
};


}

#endif /* CONFIGURATION_SCHEMA_READER_HPP */
