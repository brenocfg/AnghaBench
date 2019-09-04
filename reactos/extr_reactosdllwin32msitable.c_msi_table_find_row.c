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
struct TYPE_7__ {TYPE_1__* table; } ;
struct TYPE_6__ {scalar_t__ row_count; } ;
typedef  TYPE_2__ MSITABLEVIEW ;
typedef  int /*<<< orphan*/  MSIRECORD ;

/* Variables and functions */
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  msi_free (scalar_t__*) ; 
 scalar_t__* msi_record_to_row (TYPE_2__*,int /*<<< orphan*/ *) ; 
 scalar_t__ msi_row_matches (TYPE_2__*,scalar_t__,scalar_t__*,scalar_t__*) ; 

__attribute__((used)) static UINT msi_table_find_row( MSITABLEVIEW *tv, MSIRECORD *rec, UINT *row, UINT *column )
{
    UINT i, r = ERROR_FUNCTION_FAILED, *data;

    data = msi_record_to_row( tv, rec );
    if( !data )
        return r;
    for( i = 0; i < tv->table->row_count; i++ )
    {
        r = msi_row_matches( tv, i, data, column );
        if( r == ERROR_SUCCESS )
        {
            *row = i;
            break;
        }
    }
    msi_free( data );
    return r;
}