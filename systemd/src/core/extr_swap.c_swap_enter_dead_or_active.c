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
struct TYPE_6__ {scalar_t__ from_proc_swaps; } ;
typedef  int /*<<< orphan*/  SwapResult ;
typedef  TYPE_1__ Swap ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  swap_enter_active (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap_enter_dead (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void swap_enter_dead_or_active(Swap *s, SwapResult f) {
        assert(s);

        if (s->from_proc_swaps)
                swap_enter_active(s, f);
        else
                swap_enter_dead(s, f);
}