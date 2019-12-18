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
struct TYPE_5__ {scalar_t__ result; } ;
typedef  scalar_t__ SwapResult ;
typedef  TYPE_1__ Swap ;

/* Variables and functions */
 int /*<<< orphan*/  SWAP_ACTIVE ; 
 scalar_t__ SWAP_SUCCESS ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  swap_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void swap_enter_active(Swap *s, SwapResult f) {
        assert(s);

        if (s->result == SWAP_SUCCESS)
                s->result = f;

        swap_set_state(s, SWAP_ACTIVE);
}