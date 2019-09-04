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
struct TYPE_8__ {TYPE_1__* ops; } ;
struct TYPE_7__ {TYPE_3__* table; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* delete ) (TYPE_3__*) ;} ;
typedef  TYPE_2__ MSIDELETEVIEW ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  msi_free (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static UINT DELETE_delete( struct tagMSIVIEW *view )
{
    MSIDELETEVIEW *dv = (MSIDELETEVIEW*)view;

    TRACE("%p\n", dv );

    if( dv->table )
        dv->table->ops->delete( dv->table );

    msi_free( dv );

    return ERROR_SUCCESS;
}