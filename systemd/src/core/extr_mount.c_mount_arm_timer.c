#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_10__ {TYPE_1__* manager; } ;
struct TYPE_9__ {scalar_t__ timer_event_source; } ;
struct TYPE_8__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_2__ Mount ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  SD_EVENT_ONESHOT ; 
 TYPE_6__* UNIT (TYPE_2__*) ; 
 int /*<<< orphan*/  USEC_INFINITY ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  mount_dispatch_timer ; 
 int sd_event_add_time (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  sd_event_source_set_description (scalar_t__,char*) ; 
 int sd_event_source_set_enabled (scalar_t__,int /*<<< orphan*/ ) ; 
 int sd_event_source_set_time (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mount_arm_timer(Mount *m, usec_t usec) {
        int r;

        assert(m);

        if (m->timer_event_source) {
                r = sd_event_source_set_time(m->timer_event_source, usec);
                if (r < 0)
                        return r;

                return sd_event_source_set_enabled(m->timer_event_source, SD_EVENT_ONESHOT);
        }

        if (usec == USEC_INFINITY)
                return 0;

        r = sd_event_add_time(
                        UNIT(m)->manager->event,
                        &m->timer_event_source,
                        CLOCK_MONOTONIC,
                        usec, 0,
                        mount_dispatch_timer, m);
        if (r < 0)
                return r;

        (void) sd_event_source_set_description(m->timer_event_source, "mount-timer");

        return 0;
}