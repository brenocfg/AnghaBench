#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UINT ;
struct TYPE_8__ {size_t offset; } ;
struct TYPE_7__ {size_t col_count; size_t row_count; int /*<<< orphan*/ ** data; TYPE_2__* colinfo; } ;
typedef  TYPE_1__ MSITABLE ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 int /*<<< orphan*/  LONG_STR_BYTES ; 
 TYPE_1__* find_cached_table (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  msi_free (TYPE_2__*) ; 
 int /*<<< orphan*/  msi_free_colinfo (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/ * msi_realloc (int /*<<< orphan*/ *,size_t) ; 
 size_t msi_table_get_row_size (int /*<<< orphan*/ *,TYPE_2__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  table_get_column_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__**,size_t*) ; 

__attribute__((used)) static void msi_update_table_columns( MSIDATABASE *db, LPCWSTR name )
{
    MSITABLE *table;
    UINT size, offset, old_count;
    UINT n;

    if (!(table = find_cached_table( db, name ))) return;
    old_count = table->col_count;
    msi_free_colinfo( table->colinfo, table->col_count );
    msi_free( table->colinfo );
    table->colinfo = NULL;

    table_get_column_info( db, name, &table->colinfo, &table->col_count );
    if (!table->col_count) return;

    size = msi_table_get_row_size( db, table->colinfo, table->col_count, LONG_STR_BYTES );
    offset = table->colinfo[table->col_count - 1].offset;

    for ( n = 0; n < table->row_count; n++ )
    {
        table->data[n] = msi_realloc( table->data[n], size );
        if (old_count < table->col_count)
            memset( &table->data[n][offset], 0, size - offset );
    }
}