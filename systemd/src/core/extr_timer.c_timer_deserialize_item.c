#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  char const Unit ;
typedef  scalar_t__ TimerState ;
typedef  scalar_t__ TimerResult ;
struct TYPE_4__ {int /*<<< orphan*/  monotonic; int /*<<< orphan*/  realtime; } ;
struct TYPE_5__ {TYPE_1__ last_trigger; scalar_t__ result; scalar_t__ deserialized_state; } ;
typedef  TYPE_2__ Timer ;
typedef  char const FDSet ;

/* Variables and functions */
 TYPE_2__* TIMER (char const*) ; 
 scalar_t__ TIMER_SUCCESS ; 
 int /*<<< orphan*/  assert (char const*) ; 
 int /*<<< orphan*/  deserialize_usec (char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_unit_debug (char const*,char*,char const*) ; 
 scalar_t__ streq (char const*,char*) ; 
 scalar_t__ timer_result_from_string (char const*) ; 
 scalar_t__ timer_state_from_string (char const*) ; 

__attribute__((used)) static int timer_deserialize_item(Unit *u, const char *key, const char *value, FDSet *fds) {
        Timer *t = TIMER(u);

        assert(u);
        assert(key);
        assert(value);
        assert(fds);

        if (streq(key, "state")) {
                TimerState state;

                state = timer_state_from_string(value);
                if (state < 0)
                        log_unit_debug(u, "Failed to parse state value: %s", value);
                else
                        t->deserialized_state = state;

        } else if (streq(key, "result")) {
                TimerResult f;

                f = timer_result_from_string(value);
                if (f < 0)
                        log_unit_debug(u, "Failed to parse result value: %s", value);
                else if (f != TIMER_SUCCESS)
                        t->result = f;

        } else if (streq(key, "last-trigger-realtime"))
                (void) deserialize_usec(value, &t->last_trigger.realtime);
        else if (streq(key, "last-trigger-monotonic"))
                (void) deserialize_usec(value, &t->last_trigger.monotonic);
        else
                log_unit_debug(u, "Unknown serialization key: %s", key);

        return 0;
}