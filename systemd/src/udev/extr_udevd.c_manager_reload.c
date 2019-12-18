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
struct TYPE_5__ {int /*<<< orphan*/  rules; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  arg_children_max ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_kill_workers (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_notify (int,char*) ; 
 int /*<<< orphan*/  sd_notifyf (int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_builtin_exit () ; 
 int /*<<< orphan*/  udev_rules_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void manager_reload(Manager *manager) {

        assert(manager);

        sd_notify(false,
                  "RELOADING=1\n"
                  "STATUS=Flushing configuration...");

        manager_kill_workers(manager);
        manager->rules = udev_rules_free(manager->rules);
        udev_builtin_exit();

        sd_notifyf(false,
                   "READY=1\n"
                   "STATUS=Processing with %u children at max", arg_children_max);
}