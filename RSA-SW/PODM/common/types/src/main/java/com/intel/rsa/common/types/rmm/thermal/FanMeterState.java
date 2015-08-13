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

package com.intel.rsa.common.types.rmm.thermal;

import com.intel.rsa.common.types.ConvertableEnum;

public enum FanMeterState implements ConvertableEnum {
    LOWER_NON_CRITICAL("LowerNonCritical"),
    UPPER_NON_CRITICAL("UpperNonCritical"),
    LOWER_CRITICAL("LowerCritical"),
    UPPER_CRITICAL("UpperCritical"),
    NORMAL("Normal");

    private final String value;

    private FanMeterState(final String value) {
        this.value = value;
    }

    @Override
    public String getValue() {
        return value;
    }

    @Override
    public String toString() {
        return getValue();
    }
}
