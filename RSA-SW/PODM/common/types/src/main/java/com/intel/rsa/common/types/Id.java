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

package com.intel.rsa.common.types;

public final class Id {

    private final long value;

    private Id(long value) {
        this.value = value;
    }

    public static Id id(long value) {
        return new Id(value);
    }

    public long getValue() {
        return value;
    }

    /* used by JAX-RS */
    public static Id fromString(String value) {
        return new Id(Long.parseLong(value));
    }

    @Override
    public String toString() {
        return Long.toString(value);
    }

    @Override
    public boolean equals(Object o) {
        if (this == o) {
            return true;
        }

        if (o == null || getClass() != o.getClass()) {
            return false;
        }

        Id id = (Id) o;

        if (value != id.value) {
            return false;
        }

        return true;
    }

    @Override
    public int hashCode() {
        return Long.valueOf(value).hashCode();
    }
}
