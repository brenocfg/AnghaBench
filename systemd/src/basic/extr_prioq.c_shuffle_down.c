#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {unsigned int n_items; scalar_t__ (* compare_func ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;TYPE_1__* items; } ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_2__ Prioq ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swap (TYPE_2__*,unsigned int,unsigned int) ; 

__attribute__((used)) static unsigned shuffle_down(Prioq *q, unsigned idx) {
        assert(q);

        for (;;) {
                unsigned j, k, s;

                k = (idx+1)*2; /* right child */
                j = k-1;       /* left child */

                if (j >= q->n_items)
                        break;

                if (q->compare_func(q->items[j].data, q->items[idx].data) < 0)

                        /* So our left child is smaller than we are, let's
                         * remember this fact */
                        s = j;
                else
                        s = idx;

                if (k < q->n_items &&
                    q->compare_func(q->items[k].data, q->items[s].data) < 0)

                        /* So our right child is smaller than we are, let's
                         * remember this fact */
                        s = k;

                /* s now points to the smallest of the three items */

                if (s == idx)
                        /* No swap necessary, we're done */
                        break;

                swap(q, idx, s);
                idx = s;
        }

        return idx;
}