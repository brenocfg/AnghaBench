#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {int in_gc_queue; } ;
typedef  TYPE_1__ User ;
struct TYPE_22__ {TYPE_1__* user_gc_queue; TYPE_1__* session_gc_queue; TYPE_1__* seat_gc_queue; } ;
typedef  TYPE_1__ Session ;
typedef  TYPE_1__ Seat ;
typedef  TYPE_4__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,TYPE_1__*,TYPE_1__*) ; 
 scalar_t__ SESSION_CLOSING ; 
 int /*<<< orphan*/  assert (TYPE_4__*) ; 
 int /*<<< orphan*/  gc_queue ; 
 int /*<<< orphan*/  seat_free (TYPE_1__*) ; 
 scalar_t__ seat_may_gc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  seat_stop (TYPE_1__*,int) ; 
 int /*<<< orphan*/  session_finalize (TYPE_1__*) ; 
 int /*<<< orphan*/  session_free (TYPE_1__*) ; 
 scalar_t__ session_get_state (TYPE_1__*) ; 
 scalar_t__ session_may_gc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  session_stop (TYPE_1__*,int) ; 
 int /*<<< orphan*/  user_finalize (TYPE_1__*) ; 
 int /*<<< orphan*/  user_free (TYPE_1__*) ; 
 scalar_t__ user_may_gc (TYPE_1__*,int) ; 
 int /*<<< orphan*/  user_stop (TYPE_1__*,int) ; 

__attribute__((used)) static void manager_gc(Manager *m, bool drop_not_started) {
        Seat *seat;
        Session *session;
        User *user;

        assert(m);

        while ((seat = m->seat_gc_queue)) {
                LIST_REMOVE(gc_queue, m->seat_gc_queue, seat);
                seat->in_gc_queue = false;

                if (seat_may_gc(seat, drop_not_started)) {
                        seat_stop(seat, false);
                        seat_free(seat);
                }
        }

        while ((session = m->session_gc_queue)) {
                LIST_REMOVE(gc_queue, m->session_gc_queue, session);
                session->in_gc_queue = false;

                /* First, if we are not closing yet, initiate stopping */
                if (session_may_gc(session, drop_not_started) &&
                    session_get_state(session) != SESSION_CLOSING)
                        (void) session_stop(session, false);

                /* Normally, this should make the session referenced
                 * again, if it doesn't then let's get rid of it
                 * immediately */
                if (session_may_gc(session, drop_not_started)) {
                        (void) session_finalize(session);
                        session_free(session);
                }
        }

        while ((user = m->user_gc_queue)) {
                LIST_REMOVE(gc_queue, m->user_gc_queue, user);
                user->in_gc_queue = false;

                /* First step: queue stop jobs */
                if (user_may_gc(user, drop_not_started))
                        (void) user_stop(user, false);

                /* Second step: finalize user */
                if (user_may_gc(user, drop_not_started)) {
                        (void) user_finalize(user);
                        user_free(user);
                }
        }
}