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
struct TYPE_2__ {long long stat_fork_time; double stat_fork_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  closeListeningSockets (int /*<<< orphan*/ ) ; 
 int fork () ; 
 int /*<<< orphan*/  latencyAddSampleIfNeeded (char*,int) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  setupChildSignalHandlers () ; 
 int /*<<< orphan*/  updateDictResizePolicy () ; 
 long long ustime () ; 
 scalar_t__ zmalloc_used_memory () ; 

int redisFork() {
    int childpid;
    long long start = ustime();
    if ((childpid = fork()) == 0) {
        /* Child */
        closeListeningSockets(0);
        setupChildSignalHandlers();
    } else {
        /* Parent */
        server.stat_fork_time = ustime()-start;
        server.stat_fork_rate = (double) zmalloc_used_memory() * 1000000 / server.stat_fork_time / (1024*1024*1024); /* GB per second. */
        latencyAddSampleIfNeeded("fork",server.stat_fork_time/1000);
        if (childpid == -1) {
            return -1;
        }
        updateDictResizePolicy();
    }
    return childpid;
}