#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  SeafWTMonitor ;

/* Variables and functions */
 int /*<<< orphan*/  CFRunLoopRun () ; 
 int /*<<< orphan*/  add_command_pipe (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *
wt_monitor_job_darwin (void *vmonitor)
{
    SeafWTMonitor *monitor = (SeafWTMonitor *)vmonitor;

    add_command_pipe (monitor);
    while (1) {
        CFRunLoopRun();
    }
    return NULL;
}