#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  status_unit_format; int /*<<< orphan*/  cad_burst_action; int /*<<< orphan*/  kexec_watchdog; int /*<<< orphan*/  reboot_watchdog; int /*<<< orphan*/  runtime_watchdog; int /*<<< orphan*/  service_watchdogs; int /*<<< orphan*/  confirm_spawn; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  arg_cad_burst_action ; 
 int /*<<< orphan*/  arg_confirm_spawn ; 
 int /*<<< orphan*/  arg_kexec_watchdog ; 
 int /*<<< orphan*/  arg_reboot_watchdog ; 
 int /*<<< orphan*/  arg_runtime_watchdog ; 
 int /*<<< orphan*/  arg_service_watchdogs ; 
 int /*<<< orphan*/  arg_show_status ; 
 int /*<<< orphan*/  arg_status_unit_format ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_set_show_status (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void set_manager_settings(Manager *m) {

        assert(m);

        /* Propagates the various manager settings into the manager object, i.e. properties that effect the manager
         * itself (as opposed to just being inherited into newly allocated units, see set_manager_defaults() above). */

        m->confirm_spawn = arg_confirm_spawn;
        m->service_watchdogs = arg_service_watchdogs;
        m->runtime_watchdog = arg_runtime_watchdog;
        m->reboot_watchdog = arg_reboot_watchdog;
        m->kexec_watchdog = arg_kexec_watchdog;
        m->cad_burst_action = arg_cad_burst_action;

        manager_set_show_status(m, arg_show_status);
        m->status_unit_format = arg_status_unit_format;
}