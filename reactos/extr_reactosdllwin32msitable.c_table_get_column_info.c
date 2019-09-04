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
typedef  scalar_t__ UINT ;
typedef  int /*<<< orphan*/  MSIDATABASE ;
typedef  int /*<<< orphan*/  MSICOLUMNINFO ;
typedef  int /*<<< orphan*/  LPCWSTR ;

/* Variables and functions */
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_INVALID_PARAMETER ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  debugstr_w (int /*<<< orphan*/ ) ; 
 scalar_t__ get_tablecolumns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/ * msi_alloc (scalar_t__) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT table_get_column_info( MSIDATABASE *db, LPCWSTR name, MSICOLUMNINFO **pcols, UINT *pcount )
{
    UINT r, column_count = 0;
    MSICOLUMNINFO *columns;

    /* get the number of columns in this table */
    column_count = 0;
    r = get_tablecolumns( db, name, NULL, &column_count );
    if (r != ERROR_SUCCESS)
        return r;

    *pcount = column_count;

    /* if there are no columns, there's no table */
    if (!column_count)
        return ERROR_INVALID_PARAMETER;

    TRACE("table %s found\n", debugstr_w(name));

    columns = msi_alloc( column_count * sizeof(MSICOLUMNINFO) );
    if (!columns)
        return ERROR_FUNCTION_FAILED;

    r = get_tablecolumns( db, name, columns, &column_count );
    if (r != ERROR_SUCCESS)
    {
        msi_free( columns );
        return ERROR_FUNCTION_FAILED;
    }
    *pcols = columns;
    return r;
}