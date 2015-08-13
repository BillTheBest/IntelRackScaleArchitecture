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

package com.intel.rsa.client.api.rss;

import com.intel.rsa.client.api.actions.RsaApiActionException;

import java.net.URI;

public interface RssActions {

    /**
     * TODO: Maybe return LogicalDrive?
     *
     * @throws RsaApiActionException
     */
    URI createLogicalDrive(
            URI hostUri,
            URI storageServiceUri,
            LogicalDriveCreationRequest request)
            throws RsaApiActionException, InterruptedException;

    /**
     * TODO: Maybe return RemoteTarget ?
     *
     * @throws RsaApiActionException
     */
    URI createRemoteTarget(
            URI hostUri,
            URI storageServiceUri,
            RemoteTargetCreationRequest request) throws RsaApiActionException;
}
