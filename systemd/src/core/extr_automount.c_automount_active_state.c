#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UnitActiveState ;
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_2__ {size_t state; } ;

/* Variables and functions */
 TYPE_1__* AUTOMOUNT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * state_translation_table ; 

__attribute__((used)) static UnitActiveState automount_active_state(Unit *u) {
        assert(u);

        return state_translation_table[AUTOMOUNT(u)->state];
}