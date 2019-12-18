#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {void* data; } ;
struct TYPE_5__ {scalar_t__ n_items; TYPE_3__* items; } ;
typedef  TYPE_1__ Prioq ;

/* Variables and functions */
 int /*<<< orphan*/  remove_item (TYPE_1__*,TYPE_3__*) ; 

void *prioq_pop(Prioq *q) {
        void *data;

        if (!q)
                return NULL;

        if (q->n_items <= 0)
                return NULL;

        data = q->items[0].data;
        remove_item(q, q->items);
        return data;
}