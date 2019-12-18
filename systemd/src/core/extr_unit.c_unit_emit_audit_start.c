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
struct TYPE_5__ {scalar_t__ type; int in_audit; int /*<<< orphan*/  manager; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIT_SERVICE_START ; 
 scalar_t__ UNIT_SERVICE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_send_unit_audit (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void unit_emit_audit_start(Unit *u) {
        assert(u);

        if (u->type != UNIT_SERVICE)
                return;

        /* Write audit record if we have just finished starting up */
        manager_send_unit_audit(u->manager, u, AUDIT_SERVICE_START, true);
        u->in_audit = true;
}