#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_8__ {TYPE_2__* wv; } ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* get_column_info ) (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ MSIVIEW ;
typedef  TYPE_3__ MSIUPDATEVIEW ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT UPDATE_get_column_info( struct tagMSIVIEW *view, UINT n, LPCWSTR *name,
                                    UINT *type, BOOL *temporary, LPCWSTR *table_name )
{
    MSIUPDATEVIEW *uv = (MSIUPDATEVIEW*)view;
    MSIVIEW *wv;

    TRACE("%p %d %p %p %p %p\n", uv, n, name, type, temporary, table_name );

    wv = uv->wv;
    if( !wv )
        return ERROR_FUNCTION_FAILED;

    return wv->ops->get_column_info( wv, n, name, type, temporary, table_name );
}