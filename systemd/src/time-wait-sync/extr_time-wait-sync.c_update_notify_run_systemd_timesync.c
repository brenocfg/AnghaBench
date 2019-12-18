#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int run_systemd_timesync_wd; int /*<<< orphan*/  inotify_fd; } ;
typedef  TYPE_1__ ClockState ;

/* Variables and functions */
 int IN_CREATE ; 
 int IN_DELETE_SELF ; 
 int inotify_add_watch (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int update_notify_run_systemd_timesync(ClockState *sp) {
        sp->run_systemd_timesync_wd = inotify_add_watch(sp->inotify_fd, "/run/systemd/timesync", IN_CREATE|IN_DELETE_SELF);
        return sp->run_systemd_timesync_wd;
}