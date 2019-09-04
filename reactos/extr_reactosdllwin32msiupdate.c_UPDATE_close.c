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
struct TYPE_8__ {TYPE_2__* wv; } ;
struct TYPE_7__ {TYPE_1__* ops; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* close ) (TYPE_2__*) ;} ;
typedef  TYPE_2__ MSIVIEW ;
typedef  TYPE_3__ MSIUPDATEVIEW ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR_FUNCTION_FAILED ; 
 int /*<<< orphan*/  TRACE (char*,TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static UINT UPDATE_close( struct tagMSIVIEW *view )
{
    MSIUPDATEVIEW *uv = (MSIUPDATEVIEW*)view;
    MSIVIEW *wv;

    TRACE("%p\n", uv);

    wv = uv->wv;
    if( !wv )
        return ERROR_FUNCTION_FAILED;

    return wv->ops->close( wv );
}