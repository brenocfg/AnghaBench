#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_11__ {TYPE_1__* ops; } ;
struct TYPE_10__ {TYPE_4__* view; } ;
struct TYPE_9__ {int /*<<< orphan*/  tables; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* get_column_info ) (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ MSIWHEREVIEW ;
typedef  int /*<<< orphan*/  LPCWSTR ;
typedef  TYPE_3__ JOINTABLE ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* find_table (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT WHERE_get_column_info( struct tagMSIVIEW *view, UINT n, LPCWSTR *name,
                                   UINT *type, BOOL *temporary, LPCWSTR *table_name )
{
    MSIWHEREVIEW *wv = (MSIWHEREVIEW*)view;
    JOINTABLE *table;

    TRACE("%p %d %p %p %p %p\n", wv, n, name, type, temporary, table_name );

    if(!wv->tables)
         return ERROR_FUNCTION_FAILED;

    table = find_table(wv, n, &n);
    if (!table)
        return ERROR_FUNCTION_FAILED;

    return table->view->ops->get_column_info(table->view, n, name,
                                            type, temporary, table_name);
}