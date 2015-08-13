/*
 * Copyright (c) 2015 Intel Corporation
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.intel.rsa.podm.configuration.dto;

import com.fasterxml.jackson.annotation.JsonProperty;

public class NetworkIpV4AddressDto {
    @JsonProperty("Address")
    private String address;
    @JsonProperty("SubnetMask")
    private String subnetMask;
    @JsonProperty("AddressOrigin")
    private String addressOrigin;
    @JsonProperty("Gateway")
    private String gateway;

    public String getAddress() {
        return address;
    }

    public String getSubnetMask() {
        return subnetMask;
    }

    public String getAddressOrigin() {
        return addressOrigin;
    }

    public String getGateway() {
        return gateway;
    }

    public void setAddress(String address) {
        this.address = address;
    }

    public void setSubnetMask(String subnetMask) {
        this.subnetMask = subnetMask;
    }

    public void setAddressOrigin(String addressOrigin) {
        this.addressOrigin = addressOrigin;
    }

    public void setGateway(String gateway) {
        this.gateway = gateway;
    }
}
