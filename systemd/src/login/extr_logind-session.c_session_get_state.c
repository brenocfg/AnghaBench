#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ fifo_fd; scalar_t__ scope_job; scalar_t__ timer_event_source; scalar_t__ stopping; } ;
typedef  int /*<<< orphan*/  SessionState ;
typedef  TYPE_1__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  SESSION_ACTIVE ; 
 int /*<<< orphan*/  SESSION_CLOSING ; 
 int /*<<< orphan*/  SESSION_ONLINE ; 
 int /*<<< orphan*/  SESSION_OPENING ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ session_is_active (TYPE_1__*) ; 

SessionState session_get_state(Session *s) {
        assert(s);

        /* always check closing first */
        if (s->stopping || s->timer_event_source)
                return SESSION_CLOSING;

        if (s->scope_job || s->fifo_fd < 0)
                return SESSION_OPENING;

        if (session_is_active(s))
                return SESSION_ACTIVE;

        return SESSION_ONLINE;
}