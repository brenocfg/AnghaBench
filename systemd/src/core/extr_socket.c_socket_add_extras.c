#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_11__ {int interval; unsigned int burst; } ;
struct TYPE_12__ {int /*<<< orphan*/  exec_context; int /*<<< orphan*/  service; TYPE_1__ trigger_limit; scalar_t__ accept; } ;
typedef  TYPE_2__ Socket ;

/* Variables and functions */
 int /*<<< orphan*/ * UNIT (TYPE_2__*) ; 
 int /*<<< orphan*/  UNIT_BEFORE ; 
 int /*<<< orphan*/  UNIT_DEPENDENCY_IMPLICIT ; 
 int /*<<< orphan*/  UNIT_DEREF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UNIT_TRIGGERS ; 
 int USEC_INFINITY ; 
 int USEC_PER_SEC ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 scalar_t__ have_non_accept_socket (TYPE_2__*) ; 
 int socket_add_default_dependencies (TYPE_2__*) ; 
 int socket_add_device_dependencies (TYPE_2__*) ; 
 int socket_add_mount_dependencies (TYPE_2__*) ; 
 scalar_t__ socket_has_exec (TYPE_2__*) ; 
 int unit_add_exec_dependencies (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int unit_add_two_dependencies (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int unit_load_related_unit (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int unit_patch_contexts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unit_ref_set (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int unit_set_default_slice (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int socket_add_extras(Socket *s) {
        Unit *u = UNIT(s);
        int r;

        assert(s);

        /* Pick defaults for the trigger limit, if nothing was explicitly configured. We pick a relatively high limit
         * in Accept=yes mode, and a lower limit for Accept=no. Reason: in Accept=yes mode we are invoking accept()
         * ourselves before the trigger limit can hit, thus incoming connections are taken off the socket queue quickly
         * and reliably. This is different for Accept=no, where the spawned service has to take the incoming traffic
         * off the queues, which it might not necessarily do. Moreover, while Accept=no services are supposed to
         * process whatever is queued in one go, and thus should normally never have to be started frequently. This is
         * different for Accept=yes where each connection is processed by a new service instance, and thus frequent
         * service starts are typical. */

        if (s->trigger_limit.interval == USEC_INFINITY)
                s->trigger_limit.interval = 2 * USEC_PER_SEC;

        if (s->trigger_limit.burst == (unsigned) -1) {
                if (s->accept)
                        s->trigger_limit.burst = 200;
                else
                        s->trigger_limit.burst = 20;
        }

        if (have_non_accept_socket(s)) {

                if (!UNIT_DEREF(s->service)) {
                        Unit *x;

                        r = unit_load_related_unit(u, ".service", &x);
                        if (r < 0)
                                return r;

                        unit_ref_set(&s->service, u, x);
                }

                r = unit_add_two_dependencies(u, UNIT_BEFORE, UNIT_TRIGGERS, UNIT_DEREF(s->service), true, UNIT_DEPENDENCY_IMPLICIT);
                if (r < 0)
                        return r;
        }

        r = socket_add_mount_dependencies(s);
        if (r < 0)
                return r;

        r = socket_add_device_dependencies(s);
        if (r < 0)
                return r;

        r = unit_patch_contexts(u);
        if (r < 0)
                return r;

        if (socket_has_exec(s)) {
                r = unit_add_exec_dependencies(u, &s->exec_context);
                if (r < 0)
                        return r;
        }

        r = unit_set_default_slice(u);
        if (r < 0)
                return r;

        r = socket_add_default_dependencies(s);
        if (r < 0)
                return r;

        return 0;
}