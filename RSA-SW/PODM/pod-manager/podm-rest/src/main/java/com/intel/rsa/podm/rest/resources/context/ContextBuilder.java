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

package com.intel.rsa.podm.rest.resources.context;

import com.intel.rsa.common.types.Id;
import com.intel.rsa.podm.business.services.context.Context;
import com.intel.rsa.podm.business.services.context.ContextType;

import java.util.LinkedHashMap;
import java.util.Map;

import static com.intel.rsa.podm.business.services.context.Context.contextOf;
import static com.intel.rsa.podm.business.services.context.Context.isAcceptableChildOf;
import static java.lang.String.format;

public final class ContextBuilder {
    private final ParamNameToContextTypeMapper mapper = new ParamNameToContextTypeMapper();

    private final LinkedHashMap<String, Id> params = new LinkedHashMap<>();

    public void add(String paramName, Id value) {
        if (!mapper.contains(paramName)) {
            String msg = format("paramName '%s' is not known", paramName);
            throw new IllegalArgumentException(msg);
        }

        if (value == null) {
            throw new IllegalArgumentException("value must not be null");
        }

        params.put(paramName, value);
    }

    public Context build() throws ContextBuilderException {
        Context current = null;

        for (Map.Entry<String, Id> entry : params.entrySet()) {
            String paramName = entry.getKey();
            Id id = entry.getValue();

            ContextType type = mapper.get(paramName);

            if (!isAcceptableChildOf(type, current)) {
                String msg = format("'%s' cannot be child of '%s'", type, current);
                throw new ContextBuilderException(msg);
            }

            current = createContext(current, id, type);
        }

        if (current == null) {
            throw new ContextBuilderException("no parameters has been added");
        }

        return current;
    }

    private Context createContext(Context parent, Id id, ContextType type) {
        return parent == null
                ? contextOf(id, type)
                : parent.child(id, type);
    }
}
