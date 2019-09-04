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
struct table {int flags; int /*<<< orphan*/  entry; struct table* data; int /*<<< orphan*/  num_cols; scalar_t__ columns; scalar_t__ name; } ;
struct column {int dummy; } ;
typedef  struct table WCHAR ;

/* Variables and functions */
 int TABLE_FLAG_DYNAMIC ; 
 int /*<<< orphan*/  TRACE (char*,struct table*) ; 
 int /*<<< orphan*/  clear_table (struct table*) ; 
 int /*<<< orphan*/  free_columns (struct column*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  heap_free (struct table*) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *) ; 

void free_table( struct table *table )
{
    if (!table) return;

    clear_table( table );
    if (table->flags & TABLE_FLAG_DYNAMIC)
    {
        TRACE("destroying %p\n", table);
        heap_free( (WCHAR *)table->name );
        free_columns( (struct column *)table->columns, table->num_cols );
        heap_free( table->data );
        list_remove( &table->entry );
        heap_free( table );
    }
}