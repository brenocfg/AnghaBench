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
struct TYPE_2__ {scalar_t__ aof_state; int aof_fd; int aof_selected_db; } ;

/* Variables and functions */
 scalar_t__ AOF_OFF ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  flushAppendOnlyFile (int) ; 
 int /*<<< orphan*/  killAppendOnlyChild () ; 
 int /*<<< orphan*/  redis_fsync (int) ; 
 TYPE_1__ server ; 
 int /*<<< orphan*/  serverAssert (int) ; 

void stopAppendOnly(void) {
    serverAssert(server.aof_state != AOF_OFF);
    flushAppendOnlyFile(1);
    redis_fsync(server.aof_fd);
    close(server.aof_fd);

    server.aof_fd = -1;
    server.aof_selected_db = -1;
    server.aof_state = AOF_OFF;
    killAppendOnlyChild();
}