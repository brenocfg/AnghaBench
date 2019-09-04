#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  robj ;
typedef  int /*<<< orphan*/  redisDb ;
typedef  scalar_t__ mstime_t ;
struct TYPE_2__ {scalar_t__ lua_time_start; scalar_t__ lua_caller; scalar_t__ loading; } ;

/* Variables and functions */
 scalar_t__ getExpire (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ mstime () ; 
 TYPE_1__ server ; 

int keyIsExpired(redisDb *db, robj *key) {
    mstime_t when = getExpire(db,key);

    if (when < 0) return 0; /* No expire for this key */

    /* Don't expire anything while loading. It will be done later. */
    if (server.loading) return 0;

    /* If we are in the context of a Lua script, we pretend that time is
     * blocked to when the Lua script started. This way a key can expire
     * only the first time it is accessed and not in the middle of the
     * script execution, making propagation to slaves / AOF consistent.
     * See issue #1525 on Github for more information. */
    mstime_t now = server.lua_caller ? server.lua_time_start : mstime();

    return now > when;
}