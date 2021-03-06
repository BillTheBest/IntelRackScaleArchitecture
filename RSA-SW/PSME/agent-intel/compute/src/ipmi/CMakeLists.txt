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
    # Interface
    management_controller.cpp
    message.cpp
    request.cpp
    response.cpp

    get_device_id.cpp
    get_node_info.cpp
    get_chassis_status.cpp

    set_iscsi_field.cpp
    set_system_boot_options.cpp

    chassis_control_command.cpp

    clear_boot_valid_bit.cpp
    force_pxe_boot.cpp
    force_hdd_boot.cpp

    get_system_mac_address.cpp

    # OpenIPMI implementation.
    openipmi/management_controller.cpp
)

    set_source_files_properties(
        chassis_control_command.cpp
        COMPILE_FLAGS "-Wno-exit-time-destructors -Wno-global-constructors"
    )

if (CMAKE_CXX_COMPILER_ID MATCHES GNU)
    set_source_files_properties(
        openipmi/management_controller.cpp
        PROPERTIES COMPILE_FLAGS "-Wno-useless-cast"
    )
endif()

add_subdirectory(openipmi)

add_library(ipmi-intel OBJECT ${SOURCES})
