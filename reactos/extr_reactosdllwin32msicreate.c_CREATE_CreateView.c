#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int type; int /*<<< orphan*/  temporary; void* table; struct TYPE_12__* next; } ;
typedef  TYPE_2__ column_info ;
typedef  scalar_t__ UINT ;
struct TYPE_11__ {int /*<<< orphan*/ * ops; } ;
struct TYPE_14__ {void* hold; void* bIsTemp; TYPE_2__* col_info; void* name; TYPE_3__* db; TYPE_1__ view; } ;
struct TYPE_13__ {int /*<<< orphan*/  hdr; } ;
typedef  int /*<<< orphan*/  MSIVIEW ;
typedef  TYPE_3__ MSIDATABASE ;
typedef  TYPE_4__ MSICREATEVIEW ;
typedef  void* LPCWSTR ;
typedef  void* BOOL ;

/* Variables and functions */
 scalar_t__ ERROR_FUNCTION_FAILED ; 
 scalar_t__ ERROR_SUCCESS ; 
 void* FALSE ; 
 int MSITYPE_KEY ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*) ; 
 void* TRUE ; 
 scalar_t__ check_columns (TYPE_2__*) ; 
 int /*<<< orphan*/  create_ops ; 
 TYPE_4__* msi_alloc_zero (int) ; 
 int /*<<< orphan*/  msi_free (TYPE_4__*) ; 
 int /*<<< orphan*/  msiobj_addref (int /*<<< orphan*/ *) ; 

UINT CREATE_CreateView( MSIDATABASE *db, MSIVIEW **view, LPCWSTR table,
                        column_info *col_info, BOOL hold )
{
    MSICREATEVIEW *cv = NULL;
    UINT r;
    column_info *col;
    BOOL temp = TRUE;
    BOOL tempprim = FALSE;

    TRACE("%p\n", cv );

    r = check_columns( col_info );
    if( r != ERROR_SUCCESS )
        return r;

    cv = msi_alloc_zero( sizeof *cv );
    if( !cv )
        return ERROR_FUNCTION_FAILED;

    for( col = col_info; col; col = col->next )
    {
        if (!col->table)
            col->table = table;

        if( !col->temporary )
            temp = FALSE;
        else if ( col->type & MSITYPE_KEY )
            tempprim = TRUE;
    }

    if ( !temp && tempprim )
    {
        msi_free( cv );
        return ERROR_FUNCTION_FAILED;
    }

    /* fill the structure */
    cv->view.ops = &create_ops;
    msiobj_addref( &db->hdr );
    cv->db = db;
    cv->name = table;
    cv->col_info = col_info;
    cv->bIsTemp = temp;
    cv->hold = hold;
    *view = (MSIVIEW*) cv;

    return ERROR_SUCCESS;
}