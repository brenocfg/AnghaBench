#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ UINT ;
struct TYPE_7__ {int /*<<< orphan*/  strings; } ;
struct TYPE_6__ {scalar_t__ row_count; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ MSITABLE ;
typedef  TYPE_2__ MSIDATABASE ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  LONG_STR_BYTES ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 scalar_t__ get_table (TYPE_2__*,int /*<<< orphan*/ ,TYPE_1__**) ; 
 scalar_t__ msi_string2id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*) ; 
 scalar_t__ read_table_int (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strcmpW (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  szColumns ; 
 int /*<<< orphan*/  szStorages ; 
 int /*<<< orphan*/  szStreams ; 
 int /*<<< orphan*/  szTables ; 

BOOL TABLE_Exists( MSIDATABASE *db, LPCWSTR name )
{
    UINT r, table_id, i;
    MSITABLE *table;

    if( !strcmpW( name, szTables ) || !strcmpW( name, szColumns ) ||
        !strcmpW( name, szStreams ) || !strcmpW( name, szStorages ) )
        return TRUE;

    r = msi_string2id( db->strings, name, -1, &table_id );
    if( r != ERROR_SUCCESS )
    {
        TRACE("Couldn't find id for %s\n", debugstr_w(name));
        return FALSE;
    }

    r = get_table( db, szTables, &table );
    if( r != ERROR_SUCCESS )
    {
        ERR("table %s not available\n", debugstr_w(szTables));
        return FALSE;
    }

    for( i = 0; i < table->row_count; i++ )
    {
        if( read_table_int( table->data, i, 0, LONG_STR_BYTES ) == table_id )
            return TRUE;
    }

    return FALSE;
}