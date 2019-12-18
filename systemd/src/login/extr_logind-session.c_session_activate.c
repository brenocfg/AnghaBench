#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {TYPE_1__* pending_switch; TYPE_1__* active; } ;
struct TYPE_7__ {scalar_t__ vtnr; TYPE_4__* seat; struct TYPE_7__* user; } ;
typedef  TYPE_1__ Session ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int chvt (scalar_t__) ; 
 int /*<<< orphan*/  seat_complete_switch (TYPE_4__*) ; 
 scalar_t__ seat_has_vts (TYPE_4__*) ; 
 unsigned int session_device_try_pause_all (TYPE_1__*) ; 

int session_activate(Session *s) {
        unsigned num_pending;

        assert(s);
        assert(s->user);

        if (!s->seat)
                return -EOPNOTSUPP;

        if (s->seat->active == s)
                return 0;

        /* on seats with VTs, we let VTs manage session-switching */
        if (seat_has_vts(s->seat)) {
                if (s->vtnr == 0)
                        return -EOPNOTSUPP;

                return chvt(s->vtnr);
        }

        /* On seats without VTs, we implement session-switching in logind. We
         * try to pause all session-devices and wait until the session
         * controller acknowledged them. Once all devices are asleep, we simply
         * switch the active session and be done.
         * We save the session we want to switch to in seat->pending_switch and
         * seat_complete_switch() will perform the final switch. */

        s->seat->pending_switch = s;

        /* if no devices are running, immediately perform the session switch */
        num_pending = session_device_try_pause_all(s);
        if (!num_pending)
                seat_complete_switch(s->seat);

        return 0;
}