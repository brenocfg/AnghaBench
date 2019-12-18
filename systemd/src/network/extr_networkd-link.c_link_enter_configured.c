#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ state; struct TYPE_7__* network; } ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  LINK_STATE_CONFIGURED ; 
 scalar_t__ LINK_STATE_CONFIGURING ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  link_dirty (TYPE_1__*) ; 
 int /*<<< orphan*/  link_join_netdevs_after_configured (TYPE_1__*) ; 
 int /*<<< orphan*/  link_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void link_enter_configured(Link *link) {
        assert(link);
        assert(link->network);

        if (link->state != LINK_STATE_CONFIGURING)
                return;

        link_set_state(link, LINK_STATE_CONFIGURED);

        (void) link_join_netdevs_after_configured(link);

        link_dirty(link);
}