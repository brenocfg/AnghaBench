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
struct TYPE_3__ {int /*<<< orphan*/  timerfd_fd; int /*<<< orphan*/  timerfd_event_source; } ;
typedef  TYPE_1__ ClockState ;

/* Variables and functions */
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void clock_state_release_timerfd(ClockState *sp) {
        sp->timerfd_event_source = sd_event_source_unref(sp->timerfd_event_source);
        sp->timerfd_fd = safe_close(sp->timerfd_fd);
}