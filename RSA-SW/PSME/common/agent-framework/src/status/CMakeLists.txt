# <license_header>
#
# Copyright (c) 2015 Intel Corporation
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
# </license_header>

set(SOURCES
    module_status.cpp
    module_hardware_status.cpp
    module_software_status.cpp
)
include_directories(SYSTEM
)

set_source_files_properties(module_software_status.cpp PROPERTIES COMPILE_FLAGS
    "-Wno-old-style-cast")

add_library(status OBJECT ${SOURCES})

if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
    # GCC bug. In C++11 inititalization with {} is correct
    set_source_files_properties(module_hardware_status.cpp PROPERTIES
        COMPILE_FLAGS "-Wno-missing-field-initializers"
    )
endif()
