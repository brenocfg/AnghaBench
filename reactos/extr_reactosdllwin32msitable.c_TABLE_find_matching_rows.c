#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_11__ ;

/* Type definitions */
struct tagMSIVIEW {TYPE_2__* ops; } ;
typedef  int UINT ;
struct TYPE_16__ {int value; int row; struct TYPE_16__* next; } ;
struct TYPE_15__ {int num_cols; scalar_t__ row_size; TYPE_11__* columns; TYPE_1__* table; } ;
struct TYPE_14__ {scalar_t__ (* fetch_int ) (struct tagMSIVIEW*,int,int,int*) ;} ;
struct TYPE_13__ {int row_count; } ;
struct TYPE_12__ {scalar_t__ offset; TYPE_4__** hash_table; } ;
typedef  TYPE_3__ MSITABLEVIEW ;
typedef  TYPE_4__ const* MSIITERHANDLE ;
typedef  TYPE_4__ MSICOLUMNHASHENTRY ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,TYPE_3__*,TYPE_11__*) ; 
 int ERROR_FUNCTION_FAILED ; 
 int ERROR_INVALID_PARAMETER ; 
 int ERROR_NO_MORE_ITEMS ; 
 int ERROR_OUTOFMEMORY ; 
 scalar_t__ ERROR_SUCCESS ; 
 int MSITABLE_HASH_TABLE_SIZE ; 
 int /*<<< orphan*/  TRACE (char*,struct tagMSIVIEW*,int,int,TYPE_4__ const*) ; 
 int /*<<< orphan*/  memset (TYPE_4__**,int /*<<< orphan*/ ,int) ; 
 TYPE_4__** msi_alloc (int) ; 
 scalar_t__ stub1 (struct tagMSIVIEW*,int,int,int*) ; 

__attribute__((used)) static UINT TABLE_find_matching_rows( struct tagMSIVIEW *view, UINT col,
    UINT val, UINT *row, MSIITERHANDLE *handle )
{
    MSITABLEVIEW *tv = (MSITABLEVIEW*)view;
    const MSICOLUMNHASHENTRY *entry;

    TRACE("%p, %d, %u, %p\n", view, col, val, *handle);

    if( !tv->table )
        return ERROR_INVALID_PARAMETER;

    if( (col==0) || (col > tv->num_cols) )
        return ERROR_INVALID_PARAMETER;

    if( !tv->columns[col-1].hash_table )
    {
        UINT i;
        UINT num_rows = tv->table->row_count;
        MSICOLUMNHASHENTRY **hash_table;
        MSICOLUMNHASHENTRY *new_entry;

        if( tv->columns[col-1].offset >= tv->row_size )
        {
            ERR("Stuffed up %d >= %d\n", tv->columns[col-1].offset, tv->row_size );
            ERR("%p %p\n", tv, tv->columns );
            return ERROR_FUNCTION_FAILED;
        }

        /* allocate contiguous memory for the table and its entries so we
         * don't have to do an expensive cleanup */
        hash_table = msi_alloc(MSITABLE_HASH_TABLE_SIZE * sizeof(MSICOLUMNHASHENTRY*) +
            num_rows * sizeof(MSICOLUMNHASHENTRY));
        if (!hash_table)
            return ERROR_OUTOFMEMORY;

        memset(hash_table, 0, MSITABLE_HASH_TABLE_SIZE * sizeof(MSICOLUMNHASHENTRY*));
        tv->columns[col-1].hash_table = hash_table;

        new_entry = (MSICOLUMNHASHENTRY *)(hash_table + MSITABLE_HASH_TABLE_SIZE);

        for (i = 0; i < num_rows; i++, new_entry++)
        {
            UINT row_value;

            if (view->ops->fetch_int( view, i, col, &row_value ) != ERROR_SUCCESS)
                continue;

            new_entry->next = NULL;
            new_entry->value = row_value;
            new_entry->row = i;
            if (hash_table[row_value % MSITABLE_HASH_TABLE_SIZE])
            {
                MSICOLUMNHASHENTRY *prev_entry = hash_table[row_value % MSITABLE_HASH_TABLE_SIZE];
                while (prev_entry->next)
                    prev_entry = prev_entry->next;
                prev_entry->next = new_entry;
            }
            else
                hash_table[row_value % MSITABLE_HASH_TABLE_SIZE] = new_entry;
        }
    }

    if( !*handle )
        entry = tv->columns[col-1].hash_table[val % MSITABLE_HASH_TABLE_SIZE];
    else
        entry = (*handle)->next;

    while (entry && entry->value != val)
        entry = entry->next;

    *handle = entry;
    if (!entry)
        return ERROR_NO_MORE_ITEMS;

    *row = entry->row;

    return ERROR_SUCCESS;
}