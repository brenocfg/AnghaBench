#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ timer_event_source; TYPE_1__* manager; scalar_t__ stopping; int /*<<< orphan*/  started; } ;
struct TYPE_6__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_2__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  RELEASE_USEC ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  release_timeout_callback ; 
 int sd_event_add_time (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  usec_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int session_release(Session *s) {
        assert(s);

        if (!s->started || s->stopping)
                return 0;

        if (s->timer_event_source)
                return 0;

        return sd_event_add_time(s->manager->event,
                                 &s->timer_event_source,
                                 CLOCK_MONOTONIC,
                                 usec_add(now(CLOCK_MONOTONIC), RELEASE_USEC), 0,
                                 release_timeout_callback, s);
}