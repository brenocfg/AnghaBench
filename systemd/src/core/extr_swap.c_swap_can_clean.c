#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  Unit ;
struct TYPE_4__ {int /*<<< orphan*/  exec_context; } ;
typedef  TYPE_1__ Swap ;
typedef  int /*<<< orphan*/  ExecCleanMask ;

/* Variables and functions */
 TYPE_1__* SWAP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int exec_context_get_clean_mask (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int swap_can_clean(Unit *u, ExecCleanMask *ret) {
        Swap *s = SWAP(u);

        assert(s);

        return exec_context_get_clean_mask(&s->exec_context, ret);
}