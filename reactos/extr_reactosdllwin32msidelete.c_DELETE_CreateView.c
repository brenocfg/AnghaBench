#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_7__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_8__ {TYPE_1__ view; TYPE_1__* table; int /*<<< orphan*/ * db; } ;
typedef  TYPE_1__ MSIVIEW ;
typedef  TYPE_2__ MSIDELETEVIEW ;
typedef  int /*<<< orphan*/  MSIDATABASE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  delete_ops ; 
 TYPE_2__* msi_alloc_zero (int) ; 

UINT DELETE_CreateView( MSIDATABASE *db, MSIVIEW **view, MSIVIEW *table )
{
    MSIDELETEVIEW *dv = NULL;

    TRACE("%p\n", dv );

    dv = msi_alloc_zero( sizeof *dv );
    if( !dv )
        return ERROR_FUNCTION_FAILED;
    
    /* fill the structure */
    dv->view.ops = &delete_ops;
    dv->db = db;
    dv->table = table;

    *view = &dv->view;

    return ERROR_SUCCESS;
}