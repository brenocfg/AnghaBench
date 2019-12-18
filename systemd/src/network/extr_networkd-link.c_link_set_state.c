#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ state; } ;
typedef  scalar_t__ LinkState ;
typedef  TYPE_1__ Link ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  link_send_changed (TYPE_1__*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  link_state_to_string (scalar_t__) ; 
 int /*<<< orphan*/  log_link_debug (TYPE_1__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void link_set_state(Link *link, LinkState state) {
        assert(link);

        if (link->state == state)
                return;

        log_link_debug(link, "State changed: %s -> %s",
                       link_state_to_string(link->state),
                       link_state_to_string(state));

        link->state = state;

        link_send_changed(link, "AdministrativeState", NULL);
}