#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct prioq_item {int dummy; } ;
struct TYPE_7__ {struct prioq_item* items; } ;
typedef  TYPE_1__ Prioq ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 struct prioq_item* find_item (TYPE_1__*,void*,unsigned int*) ; 
 unsigned int shuffle_down (TYPE_1__*,unsigned int) ; 
 int /*<<< orphan*/  shuffle_up (TYPE_1__*,unsigned int) ; 

int prioq_reshuffle(Prioq *q, void *data, unsigned *idx) {
        struct prioq_item *i;
        unsigned k;

        assert(q);

        i = find_item(q, data, idx);
        if (!i)
                return 0;

        k = i - q->items;
        k = shuffle_down(q, k);
        shuffle_up(q, k);
        return 1;
}