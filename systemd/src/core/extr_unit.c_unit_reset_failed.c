#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int start_limit_hit; int /*<<< orphan*/  start_ratelimit; } ;
typedef  TYPE_1__ Unit ;
struct TYPE_8__ {int /*<<< orphan*/  (* reset_failed ) (TYPE_1__*) ;} ;

/* Variables and functions */
 TYPE_5__* UNIT_VTABLE (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  ratelimit_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

void unit_reset_failed(Unit *u) {
        assert(u);

        if (UNIT_VTABLE(u)->reset_failed)
                UNIT_VTABLE(u)->reset_failed(u);

        ratelimit_reset(&u->start_ratelimit);
        u->start_limit_hit = false;
}