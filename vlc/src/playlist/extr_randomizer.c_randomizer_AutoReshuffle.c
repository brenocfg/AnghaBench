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
struct TYPE_2__ {int size; } ;
struct randomizer {TYPE_1__ items; scalar_t__ history; scalar_t__ next; scalar_t__ head; } ;

/* Variables and functions */
 size_t NOT_SAME_BEFORE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  randomizer_DetermineOne_ (struct randomizer*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
randomizer_AutoReshuffle(struct randomizer *r)
{
    assert(r->items.size > 0);
    r->head = 0;
    r->next = 0;
    r->history = 0; /* the whole content is history */
    size_t avoid_last_n = NOT_SAME_BEFORE;
    if (avoid_last_n > r->items.size - 1)
        /* cannot ignore all */
        avoid_last_n = r->items.size - 1;
    while (avoid_last_n)
        randomizer_DetermineOne_(r, avoid_last_n--);
}