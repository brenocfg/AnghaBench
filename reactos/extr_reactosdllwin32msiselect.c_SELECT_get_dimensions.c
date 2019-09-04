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
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_6__ {TYPE_3__* table; int /*<<< orphan*/  num_cols; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* get_dimensions ) (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_2__ MSISELECTVIEW ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static UINT SELECT_get_dimensions( struct tagMSIVIEW *view, UINT *rows, UINT *cols )
{
    MSISELECTVIEW *sv = (MSISELECTVIEW*)view;

    TRACE("%p %p %p\n", sv, rows, cols );

    if( !sv->table )
         return ERROR_FUNCTION_FAILED;

    if( cols )
        *cols = sv->num_cols;

    return sv->table->ops->get_dimensions( sv->table, rows, NULL );
}