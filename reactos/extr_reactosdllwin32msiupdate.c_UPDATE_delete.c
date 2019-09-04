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
struct TYPE_11__ {TYPE_2__* db; TYPE_3__* wv; } ;
struct TYPE_10__ {TYPE_1__* ops; } ;
struct TYPE_9__ {int /*<<< orphan*/  hdr; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* delete ) (TYPE_3__*) ;} ;
typedef  TYPE_3__ MSIVIEW ;
typedef  TYPE_4__ MSIUPDATEVIEW ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_SUCCESS ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_4__*) ; 
 int /*<<< orphan*/  msi_free (TYPE_4__*) ; 
 int /*<<< orphan*/  msiobj_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static UINT UPDATE_delete( struct tagMSIVIEW *view )
{
    MSIUPDATEVIEW *uv = (MSIUPDATEVIEW*)view;
    MSIVIEW *wv;

    TRACE("%p\n", uv );

    wv = uv->wv;
    if( wv )
        wv->ops->delete( wv );
    msiobj_release( &uv->db->hdr );
    msi_free( uv );

    return ERROR_SUCCESS;
}