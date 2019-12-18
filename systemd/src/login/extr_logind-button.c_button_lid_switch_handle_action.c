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
struct TYPE_6__ {scalar_t__ handle_lid_switch_docked; scalar_t__ handle_lid_switch_ep; scalar_t__ handle_lid_switch; int /*<<< orphan*/  lid_switch_ignore_inhibited; } ;
typedef  TYPE_1__ Manager ;
typedef  scalar_t__ HandleAction ;

/* Variables and functions */
 int /*<<< orphan*/  INHIBIT_HANDLE_LID_SWITCH ; 
 scalar_t__ _HANDLE_ACTION_INVALID ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_handle_action (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int) ; 
 scalar_t__ manager_is_docked_or_external_displays (TYPE_1__*) ; 
 scalar_t__ manager_is_on_external_power () ; 

__attribute__((used)) static void button_lid_switch_handle_action(Manager *manager, bool is_edge) {
        HandleAction handle_action;

        assert(manager);

        /* If we are docked or on external power, handle the lid switch
         * differently */
        if (manager_is_docked_or_external_displays(manager))
                handle_action = manager->handle_lid_switch_docked;
        else if (manager->handle_lid_switch_ep != _HANDLE_ACTION_INVALID &&
                 manager_is_on_external_power())
                handle_action = manager->handle_lid_switch_ep;
        else
                handle_action = manager->handle_lid_switch;

        manager_handle_action(manager, INHIBIT_HANDLE_LID_SWITCH, handle_action, manager->lid_switch_ignore_inhibited, is_edge);
}