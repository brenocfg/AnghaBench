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
struct TYPE_2__ {int rdb_child_pid; int aof_child_pid; int module_child_pid; } ;

/* Variables and functions */
 TYPE_1__ server ; 

int hasActiveChildProcess() {
    return server.rdb_child_pid != -1 ||
           server.aof_child_pid != -1 ||
           server.module_child_pid != -1;
}