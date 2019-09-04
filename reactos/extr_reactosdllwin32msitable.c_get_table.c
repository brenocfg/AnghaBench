#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WCHAR ;
typedef  scalar_t__ UINT ;
struct TYPE_13__ {int /*<<< orphan*/  tables; int /*<<< orphan*/  storage; } ;
struct TYPE_12__ {int /*<<< orphan*/  entry; scalar_t__ col_count; int /*<<< orphan*/ * colinfo; int /*<<< orphan*/  persistent; int /*<<< orphan*/  name; int /*<<< orphan*/ * data_persistent; int /*<<< orphan*/ * data; scalar_t__ row_count; } ;
typedef  TYPE_1__ MSITABLE ;
typedef  TYPE_2__ MSIDATABASE ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  MSICONDITION_NONE ; 
 int /*<<< orphan*/  MSICONDITION_TRUE ; 
 TYPE_1__* find_cached_table (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_table (TYPE_1__*) ; 
 int /*<<< orphan*/  list_add_head (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lstrcpyW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int lstrlenW (int /*<<< orphan*/ ) ; 
 TYPE_1__* msi_alloc (int) ; 
 scalar_t__ read_table_from_storage (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szColumns ; 
 int /*<<< orphan*/  szTables ; 
 scalar_t__ table_get_column_info (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,scalar_t__*) ; 

__attribute__((used)) static UINT get_table( MSIDATABASE *db, LPCWSTR name, MSITABLE **table_ret )
{
    MSITABLE *table;
    UINT r;

    /* first, see if the table is cached */
    table = find_cached_table( db, name );
    if (table)
    {
        *table_ret = table;
        return ERROR_SUCCESS;
    }

    /* nonexistent tables should be interpreted as empty tables */
    table = msi_alloc( sizeof(MSITABLE) + lstrlenW( name ) * sizeof(WCHAR) );
    if (!table)
        return ERROR_FUNCTION_FAILED;

    table->row_count = 0;
    table->data = NULL;
    table->data_persistent = NULL;
    table->colinfo = NULL;
    table->col_count = 0;
    table->persistent = MSICONDITION_TRUE;
    lstrcpyW( table->name, name );

    if (!strcmpW( name, szTables ) || !strcmpW( name, szColumns ))
        table->persistent = MSICONDITION_NONE;

    r = table_get_column_info( db, name, &table->colinfo, &table->col_count );
    if (r != ERROR_SUCCESS)
    {
        free_table( table );
        return r;
    }
    r = read_table_from_storage( db, table, db->storage );
    if (r != ERROR_SUCCESS)
    {
        free_table( table );
        return r;
    }
    list_add_head( &db->tables, &table->entry );
    *table_ret = table;
    return ERROR_SUCCESS;
}