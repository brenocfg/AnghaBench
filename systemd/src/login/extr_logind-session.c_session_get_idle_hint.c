#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ usec_t ;
typedef  int /*<<< orphan*/  dual_timestamp ;
struct TYPE_6__ {int idle_hint; TYPE_1__* manager; int /*<<< orphan*/  idle_hint_timestamp; int /*<<< orphan*/  leader; scalar_t__ tty; int /*<<< orphan*/  type; } ;
struct TYPE_5__ {scalar_t__ idle_action_usec; } ;
typedef  TYPE_2__ Session ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 scalar_t__ SESSION_TYPE_IS_GRAPHICAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  dual_timestamp_from_realtime (int /*<<< orphan*/ *,scalar_t__) ; 
 int get_process_ctty_atime (int /*<<< orphan*/ ,scalar_t__*) ; 
 int get_tty_atime (scalar_t__,scalar_t__*) ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 
 scalar_t__ pid_is_valid (int /*<<< orphan*/ ) ; 

int session_get_idle_hint(Session *s, dual_timestamp *t) {
        usec_t atime = 0, n;
        int r;

        assert(s);

        /* Explicit idle hint is set */
        if (s->idle_hint) {
                if (t)
                        *t = s->idle_hint_timestamp;

                return s->idle_hint;
        }

        /* Graphical sessions should really implement a real
         * idle hint logic */
        if (SESSION_TYPE_IS_GRAPHICAL(s->type))
                goto dont_know;

        /* For sessions with an explicitly configured tty, let's check
         * its atime */
        if (s->tty) {
                r = get_tty_atime(s->tty, &atime);
                if (r >= 0)
                        goto found_atime;
        }

        /* For sessions with a leader but no explicitly configured
         * tty, let's check the controlling tty of the leader */
        if (pid_is_valid(s->leader)) {
                r = get_process_ctty_atime(s->leader, &atime);
                if (r >= 0)
                        goto found_atime;
        }

dont_know:
        if (t)
                *t = s->idle_hint_timestamp;

        return 0;

found_atime:
        if (t)
                dual_timestamp_from_realtime(t, atime);

        n = now(CLOCK_REALTIME);

        if (s->manager->idle_action_usec <= 0)
                return 0;

        return atime + s->manager->idle_action_usec <= n;
}