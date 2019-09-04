#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  int UINT ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_6__ {int num_cols; int* cols; TYPE_3__* table; } ;
struct TYPE_5__ {int (* get_column_info ) (TYPE_3__*,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ MSISELECTVIEW ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int ERROR_FUNCTION_FAILED ; 
 int ERROR_SUCCESS ; 
 int /*<<< orphan*/  FALSE ; 
 int MSITYPE_UNKNOWN ; 
 int MSITYPE_VALID ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int stub1 (TYPE_3__*,int,int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  szEmpty ; 

__attribute__((used)) static UINT SELECT_get_column_info( struct tagMSIVIEW *view, UINT n, LPCWSTR *name,
                                    UINT *type, BOOL *temporary, LPCWSTR *table_name )
{
    MSISELECTVIEW *sv = (MSISELECTVIEW*)view;

    TRACE("%p %d %p %p %p %p\n", sv, n, name, type, temporary, table_name );

    if( !sv->table )
         return ERROR_FUNCTION_FAILED;

    if( !n || n > sv->num_cols )
         return ERROR_FUNCTION_FAILED;

    n = sv->cols[ n - 1 ];
    if( !n )
    {
        if (name) *name = szEmpty;
        if (type) *type = MSITYPE_UNKNOWN | MSITYPE_VALID;
        if (temporary) *temporary = FALSE;
        if (table_name) *table_name = szEmpty;
        return ERROR_SUCCESS;
    }
    return sv->table->ops->get_column_info( sv->table, n, name,
                                            type, temporary, table_name );
}