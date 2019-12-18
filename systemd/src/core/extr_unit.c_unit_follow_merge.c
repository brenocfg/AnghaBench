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
struct TYPE_6__ {scalar_t__ load_state; struct TYPE_6__* merged_into; } ;
typedef  TYPE_1__ Unit ;

/* Variables and functions */
 scalar_t__ UNIT_MERGED ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_se (TYPE_1__*) ; 

Unit* unit_follow_merge(Unit *u) {
        assert(u);

        while (u->load_state == UNIT_MERGED)
                assert_se(u = u->merged_into);

        return u;
}