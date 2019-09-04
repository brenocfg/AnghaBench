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
struct table {scalar_t__ num_rows; int /*<<< orphan*/ * data; scalar_t__ num_rows_allocated; scalar_t__ fill; } ;
typedef  scalar_t__ UINT ;

/* Variables and functions */
 int /*<<< orphan*/  free_row_values (struct table*,scalar_t__) ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ *) ; 

void clear_table( struct table *table )
{
    UINT i;

    if (!table->data) return;

    for (i = 0; i < table->num_rows; i++) free_row_values( table, i );
    if (table->fill)
    {
        table->num_rows = 0;
        table->num_rows_allocated = 0;
        heap_free( table->data );
        table->data = NULL;
    }
}