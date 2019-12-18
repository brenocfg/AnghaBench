#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/ * exec; int /*<<< orphan*/ * conditions; int /*<<< orphan*/  listen; int /*<<< orphan*/  triggers; int /*<<< orphan*/  triggered_by; int /*<<< orphan*/  dropin_paths; int /*<<< orphan*/  documentation; } ;
typedef  TYPE_1__ UnitStatusInfo ;
typedef  int /*<<< orphan*/  UnitCondition ;
typedef  int /*<<< orphan*/  ExecStatusInfo ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  conditions ; 
 int /*<<< orphan*/  exec ; 
 int /*<<< orphan*/  exec_status_info_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_condition_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void unit_status_info_free(UnitStatusInfo *info) {
        ExecStatusInfo *p;
        UnitCondition *c;

        strv_free(info->documentation);
        strv_free(info->dropin_paths);
        strv_free(info->triggered_by);
        strv_free(info->triggers);
        strv_free(info->listen);

        while ((c = info->conditions)) {
                LIST_REMOVE(conditions, info->conditions, c);
                unit_condition_free(c);
        }

        while ((p = info->exec)) {
                LIST_REMOVE(exec, info->exec, p);
                exec_status_info_free(p);
        }
}