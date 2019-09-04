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
typedef  int /*<<< orphan*/  time_t ;
struct tm {int /*<<< orphan*/  tm_isdst; } ;
struct TYPE_2__ {int /*<<< orphan*/  daylight_active; int /*<<< orphan*/  unixtime; int /*<<< orphan*/  mstime; } ;

/* Variables and functions */
 int /*<<< orphan*/  atomicSet (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  localtime_r (int /*<<< orphan*/ *,struct tm*) ; 
 int /*<<< orphan*/  mstime () ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  time (int /*<<< orphan*/ *) ; 

void updateCachedTime(void) {
    time_t unixtime = time(NULL);
    atomicSet(server.unixtime,unixtime);
    server.mstime = mstime();

    /* To get information about daylight saving time, we need to call localtime_r
     * and cache the result. However calling localtime_r in this context is safe
     * since we will never fork() while here, in the main thread. The logging
     * function will call a thread safe version of localtime that has no locks. */
    struct tm tm;
    localtime_r(&server.unixtime,&tm);
    server.daylight_active = tm.tm_isdst;
}