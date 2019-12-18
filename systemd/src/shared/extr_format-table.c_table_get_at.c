#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  TableCell ;
typedef  int /*<<< orphan*/  Table ;

/* Variables and functions */
 void const* table_get (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * table_get_cell (int /*<<< orphan*/ *,size_t,size_t) ; 

const void* table_get_at(Table *t, size_t row, size_t column) {
        TableCell *cell;

        cell = table_get_cell(t, row, column);
        if (!cell)
                return NULL;

        return table_get(t, cell);
}