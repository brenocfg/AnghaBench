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
struct table {size_t num_cols; TYPE_1__* columns; } ;
typedef  size_t UINT ;
struct TYPE_2__ {int type; } ;
typedef  scalar_t__ LONGLONG ;
typedef  scalar_t__ INT_PTR ;

/* Variables and functions */
 size_t CIM_DATETIME ; 
 size_t CIM_FLAG_ARRAY ; 
 size_t CIM_STRING ; 
 size_t CIM_TYPE_MASK ; 
 int COL_FLAG_DYNAMIC ; 
 size_t COL_TYPE_MASK ; 
 scalar_t__ S_OK ; 
 int /*<<< orphan*/  destroy_array (void*,size_t) ; 
 scalar_t__ get_value (struct table const*,size_t,size_t,scalar_t__*) ; 
 int /*<<< orphan*/  heap_free (void*) ; 

void free_row_values( const struct table *table, UINT row )
{
    UINT i, type;
    LONGLONG val;

    for (i = 0; i < table->num_cols; i++)
    {
        if (!(table->columns[i].type & COL_FLAG_DYNAMIC)) continue;

        type = table->columns[i].type & COL_TYPE_MASK;
        if (type == CIM_STRING || type == CIM_DATETIME)
        {
            if (get_value( table, row, i, &val ) == S_OK) heap_free( (void *)(INT_PTR)val );
        }
        else if (type & CIM_FLAG_ARRAY)
        {
            if (get_value( table, row, i, &val ) == S_OK)
                destroy_array( (void *)(INT_PTR)val, type & CIM_TYPE_MASK );
        }
    }
}