#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int stopping; int /*<<< orphan*/  user; scalar_t__ seat; int /*<<< orphan*/  timer_event_source; int /*<<< orphan*/  started; } ;
typedef  TYPE_1__ Session ;

/* Variables and functions */
 int ESTALE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  seat_evict_position (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  session_remove_fifo (TYPE_1__*) ; 
 int /*<<< orphan*/  session_save (TYPE_1__*) ; 
 int session_stop_scope (TYPE_1__*,int) ; 
 int /*<<< orphan*/  user_elect_display (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  user_save (int /*<<< orphan*/ ) ; 

int session_stop(Session *s, bool force) {
        int r;

        assert(s);

        /* This is called whenever we begin with tearing down a session record. It's called in four cases: explicit API
         * request via the bus (either directly for the session object or for the seat or user object this session
         * belongs to; 'force' is true), or due to automatic GC (i.e. scope vanished; 'force' is false), or because the
         * session FIFO saw an EOF ('force' is false), or because the release timer hit ('force' is false). */

        if (!s->user)
                return -ESTALE;
        if (!s->started)
                return 0;
        if (s->stopping)
                return 0;

        s->timer_event_source = sd_event_source_unref(s->timer_event_source);

        if (s->seat)
                seat_evict_position(s->seat, s);

        /* We are going down, don't care about FIFOs anymore */
        session_remove_fifo(s);

        /* Kill cgroup */
        r = session_stop_scope(s, force);

        s->stopping = true;

        user_elect_display(s->user);

        session_save(s);
        user_save(s->user);

        return r;
}