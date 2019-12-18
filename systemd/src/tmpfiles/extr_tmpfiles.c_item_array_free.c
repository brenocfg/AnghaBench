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
struct TYPE_6__ {size_t n_items; scalar_t__ items; int /*<<< orphan*/  children; } ;
typedef  TYPE_1__ ItemArray ;

/* Variables and functions */
 int /*<<< orphan*/  free (scalar_t__) ; 
 int /*<<< orphan*/  item_free_contents (scalar_t__) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  set_free (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ItemArray* item_array_free(ItemArray *a) {
        size_t n;

        if (!a)
                return NULL;

        for (n = 0; n < a->n_items; n++)
                item_free_contents(a->items + n);

        set_free(a->children);
        free(a->items);
        return mfree(a);
}