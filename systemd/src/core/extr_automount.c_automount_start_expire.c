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
typedef  scalar_t__ usec_t ;
struct TYPE_10__ {TYPE_1__* manager; } ;
struct TYPE_9__ {int timeout_idle_usec; scalar_t__ expire_event_source; } ;
struct TYPE_8__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_2__ Automount ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ MAX (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SD_EVENT_ONESHOT ; 
 TYPE_6__* UNIT (TYPE_2__*) ; 
 int /*<<< orphan*/  USEC_PER_SEC ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  automount_dispatch_expire ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 
 int sd_event_add_time (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  sd_event_source_set_description (scalar_t__,char*) ; 
 int sd_event_source_set_enabled (scalar_t__,int /*<<< orphan*/ ) ; 
 int sd_event_source_set_time (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int automount_start_expire(Automount *a) {
        int r;
        usec_t timeout;

        assert(a);

        if (a->timeout_idle_usec == 0)
                return 0;

        timeout = now(CLOCK_MONOTONIC) + MAX(a->timeout_idle_usec/3, USEC_PER_SEC);

        if (a->expire_event_source) {
                r = sd_event_source_set_time(a->expire_event_source, timeout);
                if (r < 0)
                        return r;

                return sd_event_source_set_enabled(a->expire_event_source, SD_EVENT_ONESHOT);
        }

        r = sd_event_add_time(
                        UNIT(a)->manager->event,
                        &a->expire_event_source,
                        CLOCK_MONOTONIC, timeout, 0,
                        automount_dispatch_expire, a);
        if (r < 0)
                return r;

        (void) sd_event_source_set_description(a->expire_event_source, "automount-expire");

        return 0;
}