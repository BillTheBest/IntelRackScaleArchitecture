/**
 * Copyright (c)  2015, Intel Corporation.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *   http://www.apache.org/licenses/LICENSE-2.0
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */


#ifndef _MEMDB_H_
#define _MEMDB_H_

#include "librmmlog/rmmlog.h"
#include "libutils/types.h"

#define MEMDB_DEBUG(format, args...)	rmm_log(DBG, format, ##args)
#define MEMDB_ERR(format, args...)		rmm_log(ERROR, format, ##args)
#define MEMDB_INFO(format, args...)		rmm_log(INFO, format, ##args)

extern bool snapshot_in_progress;

#endif
