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
typedef  scalar_t__ UINT ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_6__ {TYPE_3__* table; } ;
struct TYPE_5__ {scalar_t__ (* get_dimensions ) (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*) ;} ;
typedef  TYPE_2__ MSIDELETEVIEW ;

/* Variables and functions */
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*,scalar_t__*,scalar_t__*) ; 
 scalar_t__ stub1 (TYPE_3__*,int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static UINT DELETE_get_dimensions( struct tagMSIVIEW *view, UINT *rows, UINT *cols )
{
    MSIDELETEVIEW *dv = (MSIDELETEVIEW*)view;

    TRACE("%p %p %p\n", dv, rows, cols );

    if( !dv->table )
         return ERROR_FUNCTION_FAILED;

    *rows = 0;

    return dv->table->ops->get_dimensions( dv->table, NULL, cols );
}