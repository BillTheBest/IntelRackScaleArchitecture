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

package com.intel.rsa.podm.discovery.external.mapper.psme;

import com.intel.rsa.client.api.reader.psme.PsmeDrawer;
import com.intel.rsa.podm.business.entities.assets.Drawer;
import com.intel.rsa.podm.discovery.external.mapper.DomainObjectMapper;

import javax.enterprise.context.Dependent;

@Dependent
public class DrawerMapper extends DomainObjectMapper<PsmeDrawer, Drawer> {

    public DrawerMapper() {
        super(PsmeDrawer.class, Drawer.class);
    }

    @Override
    protected void performNotAutomatedMapping(PsmeDrawer source, Drawer target) {
        target.updateModified();
    }
}
