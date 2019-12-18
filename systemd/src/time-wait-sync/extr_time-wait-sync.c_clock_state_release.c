#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  inotify_fd; int /*<<< orphan*/  inotify_event_source; } ;
typedef  TYPE_1__ ClockState ;

/* Variables and functions */
 int /*<<< orphan*/  clock_state_release_timerfd (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clock_state_release(ClockState *sp) {
        clock_state_release_timerfd(sp);
        sp->inotify_event_source = sd_event_source_unref(sp->inotify_event_source);
        sp->inotify_fd = safe_close(sp->inotify_fd);
}