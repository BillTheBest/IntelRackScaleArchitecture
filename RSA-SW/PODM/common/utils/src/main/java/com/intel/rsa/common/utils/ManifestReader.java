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

package com.intel.rsa.common.utils;

import com.intel.rsa.common.logger.Logger;
import com.intel.rsa.common.logger.LoggerFactory;

import java.io.IOException;
import java.io.InputStream;
import java.net.URL;
import java.util.Collection;
import java.util.Collections;
import java.util.Enumeration;
import java.util.LinkedList;
import java.util.jar.Manifest;

/**
 * Class for obtaining MANIFEST.MF contents. Works within limits of a single class loader.
 */
public class ManifestReader {

    private static final String MANIFEST_PATH = "/META-INF/MANIFEST.MF";

    private static final Logger LOGGER = LoggerFactory.getLogger(ManifestReader.class.getSimpleName());

    public Manifest findManifestByEntry(String entryHeader, String entryValue) {
        Iterable<Manifest> availableManifests = getAvailableManifests();

        for (Manifest manifest : availableManifests) {
            if (containsEntry(manifest, entryHeader, entryValue)) {
                return manifest;
            }
        }
        return null;
    }

    private static boolean containsEntry(Manifest manifest, String entryHeader, String entryValue) {
        final String actualManifestTitle = manifest.getMainAttributes().getValue(entryHeader);
        if (entryValue.equals(actualManifestTitle)) {
            return true;
        }
        return false;
    }

    private static Iterable<Manifest> getAvailableManifests() {
        Collection<Manifest> manifests = new LinkedList<>();
        for (URL manifestUrl : getManifestUrls()) {
            Manifest manifest = readManifestFromUrl(manifestUrl);
            if (manifest != null) {
                manifests.add(manifest);
            }
        }
        return manifests;
    }

    private static Iterable<URL> getManifestUrls() {
        Collection<URL> manifestPath = new LinkedList<>();
        try {
            final Enumeration<URL> resources = ManifestReader.class.getClassLoader().getResources(MANIFEST_PATH);
            manifestPath.addAll(Collections.list(resources));
        } catch (IOException e) {
            LOGGER.e("Loading manifests urls failed.");
        }
        return manifestPath;
    }

    private static Manifest readManifestFromUrl(URL manifestUrl) {
        try (InputStream inputStream = manifestUrl.openStream();) {
            return new Manifest(inputStream);
        } catch (IOException e) {
            LOGGER.w("Skipping manifest {} due to IO error.", manifestUrl.getPath());
        }
        return null;
    }
}
