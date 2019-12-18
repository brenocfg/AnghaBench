#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ type; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_10__ {int /*<<< orphan*/  (* done ) (TYPE_1__*) ;} ;
typedef  int /*<<< orphan*/  ExecContext ;
typedef  int /*<<< orphan*/  CGroupContext ;

/* Variables and functions */
 TYPE_7__* UNIT_VTABLE (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  cgroup_context_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exec_context_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/ * unit_get_cgroup_context (TYPE_1__*) ; 
 int /*<<< orphan*/ * unit_get_exec_context (TYPE_1__*) ; 

__attribute__((used)) static void unit_done(Unit *u) {
        ExecContext *ec;
        CGroupContext *cc;

        assert(u);

        if (u->type < 0)
                return;

        if (UNIT_VTABLE(u)->done)
                UNIT_VTABLE(u)->done(u);

        ec = unit_get_exec_context(u);
        if (ec)
                exec_context_done(ec);

        cc = unit_get_cgroup_context(u);
        if (cc)
                cgroup_context_done(cc);
}