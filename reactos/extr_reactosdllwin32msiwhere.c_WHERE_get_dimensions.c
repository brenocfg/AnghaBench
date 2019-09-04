#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_3__ {int /*<<< orphan*/  col_count; int /*<<< orphan*/  row_count; int /*<<< orphan*/  reorder; int /*<<< orphan*/  tables; } ;
typedef  TYPE_1__ MSIWHEREVIEW ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT WHERE_get_dimensions( struct tagMSIVIEW *view, UINT *rows, UINT *cols )
{
    MSIWHEREVIEW *wv = (MSIWHEREVIEW*)view;

    TRACE("%p %p %p\n", wv, rows, cols );

    if(!wv->tables)
         return ERROR_FUNCTION_FAILED;

    if (rows)
    {
        if (!wv->reorder)
            return ERROR_FUNCTION_FAILED;
        *rows = wv->row_count;
    }

    if (cols)
        *cols = wv->col_count;

    return ERROR_SUCCESS;
}