#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct tagMSIVIEW {int dummy; } ;
typedef  int /*<<< orphan*/  UINT ;
struct TYPE_12__ {TYPE_1__* ops; } ;
struct TYPE_11__ {TYPE_2__* db; struct TYPE_11__* order_info; scalar_t__ table_count; struct TYPE_11__* tables; struct TYPE_11__* next; TYPE_5__* view; } ;
struct TYPE_10__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_9__ {int /*<<< orphan*/  (* delete ) (TYPE_5__*) ;} ;
typedef  TYPE_3__ MSIWHEREVIEW ;
typedef  TYPE_3__ JOINTABLE ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  free_reorder (TYPE_3__*) ; 
 int /*<<< orphan*/  msi_free (TYPE_3__*) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_5__*) ; 

__attribute__((used)) static UINT WHERE_delete( struct tagMSIVIEW *view )
{
    MSIWHEREVIEW *wv = (MSIWHEREVIEW*)view;
    JOINTABLE *table = wv->tables;

    TRACE("%p\n", wv );

    while(table)
    {
        JOINTABLE *next;

        table->view->ops->delete(table->view);
        table->view = NULL;
        next = table->next;
        msi_free(table);
        table = next;
    }
    wv->tables = NULL;
    wv->table_count = 0;

    free_reorder(wv);

    msi_free(wv->order_info);
    wv->order_info = NULL;

    msiobj_release( &wv->db->hdr );
    msi_free( wv );

    return ERROR_SUCCESS;
}