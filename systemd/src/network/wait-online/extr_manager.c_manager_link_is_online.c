#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ required_operstate; scalar_t__ operational_state; int /*<<< orphan*/  state; } ;
struct TYPE_7__ {scalar_t__ required_operstate; } ;
typedef  TYPE_1__ Manager ;
typedef  scalar_t__ LinkOperationalState ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  EAGAIN ; 
 scalar_t__ STR_IN_SET (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  SYNTHETIC_ERRNO (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_operstate_to_string (scalar_t__) ; 
 int /*<<< orphan*/  log_link_debug (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int log_link_debug_errno (TYPE_2__*,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int manager_link_is_online(Manager *m, Link *l, LinkOperationalState s) {
        /* This returns the following:
         * -EAGAIN: not processed by udev or networkd
         *       0: operstate is not enough
         *       1: online */

        if (!l->state)
                return log_link_debug_errno(l, SYNTHETIC_ERRNO(EAGAIN),
                                            "link has not yet been processed by udev");

        if (STR_IN_SET(l->state, "configuring", "pending"))
                return log_link_debug_errno(l, SYNTHETIC_ERRNO(EAGAIN),
                                            "link is being processed by networkd");

        if (s < 0)
                s = m->required_operstate >= 0 ? m->required_operstate : l->required_operstate;

        if (l->operational_state < s) {
                log_link_debug(l, "Operational state '%s' is below '%s'",
                               link_operstate_to_string(l->operational_state),
                               link_operstate_to_string(s));
                return 0;
        }

        return 1;
}