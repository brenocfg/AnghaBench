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
typedef  int /*<<< orphan*/  TableCell ;
struct TYPE_4__ {size_t n_cells; int /*<<< orphan*/ * data; int /*<<< orphan*/  n_columns; int /*<<< orphan*/  n_allocated; } ;
typedef  TYPE_1__ Table ;

/* Variables and functions */
 int ENOMEM ; 
 int ENXIO ; 
 int /*<<< orphan*/  GREEDY_REALLOC (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MAX (int,int /*<<< orphan*/ ) ; 
 size_t TABLE_CELL_TO_INDEX (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  table_data_ref (int /*<<< orphan*/ ) ; 

int table_dup_cell(Table *t, TableCell *cell) {
        size_t i;

        assert(t);

        /* Add the data of the specified cell a second time as a new cell to the end. */

        i = TABLE_CELL_TO_INDEX(cell);
        if (i >= t->n_cells)
                return -ENXIO;

        if (!GREEDY_REALLOC(t->data, t->n_allocated, MAX(t->n_cells + 1, t->n_columns)))
                return -ENOMEM;

        t->data[t->n_cells++] = table_data_ref(t->data[i]);
        return 0;
}