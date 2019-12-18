#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ state; int /*<<< orphan*/  state_file; TYPE_1__* network; } ;
struct TYPE_9__ {int /*<<< orphan*/  bond; int /*<<< orphan*/  bridge; } ;
typedef  TYPE_2__ Link ;

/* Variables and functions */
 scalar_t__ LINK_STATE_LINGER ; 
 int /*<<< orphan*/  link_detach_from_manager (TYPE_2__*) ; 
 int /*<<< orphan*/  link_drop_from_master (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  link_free_carrier_maps (TYPE_2__*) ; 
 int /*<<< orphan*/  link_set_state (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  log_link_debug (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 

void link_drop(Link *link) {
        if (!link || link->state == LINK_STATE_LINGER)
                return;

        link_set_state(link, LINK_STATE_LINGER);

        link_free_carrier_maps(link);

        if (link->network) {
                link_drop_from_master(link, link->network->bridge);
                link_drop_from_master(link, link->network->bond);
        }

        log_link_debug(link, "Link removed");

        (void) unlink(link->state_file);
        link_detach_from_manager(link);
}