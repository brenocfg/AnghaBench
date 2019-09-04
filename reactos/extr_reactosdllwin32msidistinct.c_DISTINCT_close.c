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
struct TYPE_6__ {TYPE_3__* table; scalar_t__ row_count; int /*<<< orphan*/ * translation; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* close ) (TYPE_3__*) ;} ;
typedef  TYPE_2__ MSIDISTINCTVIEW ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  msi_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static UINT DISTINCT_close( struct tagMSIVIEW *view )
{
    MSIDISTINCTVIEW *dv = (MSIDISTINCTVIEW*)view;

    TRACE("%p\n", dv );

    if( !dv->table )
         return ERROR_FUNCTION_FAILED;

    msi_free( dv->translation );
    dv->translation = NULL;
    dv->row_count = 0;

    return dv->table->ops->close( dv->table );
}