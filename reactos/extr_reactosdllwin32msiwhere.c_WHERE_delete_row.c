#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  scalar_t__ UINT ;
struct TYPE_9__ {TYPE_2__* ops; } ;
struct TYPE_8__ {int table_count; TYPE_1__* tables; } ;
struct TYPE_7__ {scalar_t__ (* delete_row ) (TYPE_4__*,scalar_t__) ;} ;
struct TYPE_6__ {TYPE_4__* view; } ;
typedef  TYPE_3__ MSIWHEREVIEW ;

/* Variables and functions */
 scalar_t__ ERROR_CALL_NOT_IMPLEMENTED ; 
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,struct tagMSIVIEW*,scalar_t__) ; 
 scalar_t__ find_row (TYPE_3__*,scalar_t__,scalar_t__**) ; 
 scalar_t__ stub1 (TYPE_4__*,scalar_t__) ; 

__attribute__((used)) static UINT WHERE_delete_row(struct tagMSIVIEW *view, UINT row)
{
    MSIWHEREVIEW *wv = (MSIWHEREVIEW *)view;
    UINT r;
    UINT *rows;

    TRACE("(%p %d)\n", view, row);

    if (!wv->tables)
        return ERROR_FUNCTION_FAILED;

    r = find_row(wv, row, &rows);
    if ( r != ERROR_SUCCESS )
        return r;

    if (wv->table_count > 1)
        return ERROR_CALL_NOT_IMPLEMENTED;

    return wv->tables->view->ops->delete_row(wv->tables->view, rows[0]);
}