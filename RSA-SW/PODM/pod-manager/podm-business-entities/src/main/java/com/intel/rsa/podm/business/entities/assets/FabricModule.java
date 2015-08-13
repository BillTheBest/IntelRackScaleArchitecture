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

package com.intel.rsa.podm.business.entities.assets;

import com.intel.rsa.common.types.Health;
import com.intel.rsa.common.types.State;
import com.intel.rsa.podm.business.entities.assets.links.AssetLink;
import com.intel.rsa.podm.business.entities.base.DomainObjectProperty;

import javax.enterprise.context.Dependent;
import javax.transaction.Transactional;
import java.util.Collection;

import static com.intel.rsa.common.utils.IterableHelper.single;
import static com.intel.rsa.podm.business.entities.base.DomainObjectProperties.enumProperty;

@Dependent
@Transactional(Transactional.TxType.REQUIRED)
public class FabricModule extends ManagedAsset {

    public static final DomainObjectProperty<Health> HEALTH = enumProperty("health", Health.class);
    public static final DomainObjectProperty<State> STATE = enumProperty("state", State.class);

    public Drawer getDrawer() {
        try {
            return single(getLinked(AssetLink.CONTAINED_BY, Drawer.class));
        } catch (IllegalStateException e) {
            throw new IllegalStateException("Fabric Module has to be contained by exactly one Drawer", e);
        }
    }

    public Health getHealth() {
        return getProperty(HEALTH);
    }

    public void setHealth(Health health) {
        setProperty(HEALTH, health);
    }

    public State getState() {
        return getProperty(STATE);
    }

    public void setState(State state) {
        setProperty(STATE, state);
    }

    public Collection<Switch> getSwitches() {
        return getLinked(AssetLink.CONTAINS, Switch.class);
    }
}
