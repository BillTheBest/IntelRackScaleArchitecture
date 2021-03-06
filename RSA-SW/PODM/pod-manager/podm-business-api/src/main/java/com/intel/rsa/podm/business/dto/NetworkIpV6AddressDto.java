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

package com.intel.rsa.podm.business.dto;

import com.intel.rsa.common.types.AddressState;

public final class NetworkIpV6AddressDto {
    private final String address;
    private final Integer prefixLength;
    private final String addressOrigin;
    private final AddressState addressState;

    private NetworkIpV6AddressDto(Builder builder) {
        address = builder.address;
        prefixLength = builder.prefixLength;
        addressOrigin = builder.addressOrigin;
        addressState = builder.addressState;
    }

    public String getAddress() {
        return address;
    }

    public Integer getPrefixLength() {
        return prefixLength;
    }

    public String getAddressOrigin() {
        return addressOrigin;
    }

    public AddressState getAddressState() {
        return addressState;
    }

    public static Builder newBuilder() {
        return new Builder();
    }

    public static final class Builder {
        private String address;
        private Integer prefixLength;
        private String addressOrigin;
        private AddressState addressState;

        private Builder() {
        }

        public Builder address(String address) {
            this.address = address;
            return this;
        }

        public Builder prefixLength(Integer prefixLength) {
            this.prefixLength = prefixLength;
            return this;
        }

        public Builder addressOrigin(String addressOrigin) {
            this.addressOrigin = addressOrigin;
            return this;
        }

        public Builder addressState(AddressState addressState) {
            this.addressState = addressState;
            return this;
        }

        public NetworkIpV6AddressDto build() {
            return new NetworkIpV6AddressDto(this);
        }
    }
}
