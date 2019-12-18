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
struct TYPE_7__ {void* setResizeCb; void* opaque; } ;
typedef  TYPE_1__ wextern_t ;
struct TYPE_8__ {int /*<<< orphan*/ * ops; int /*<<< orphan*/  type; TYPE_1__* sys; } ;
typedef  TYPE_2__ vout_window_t ;

/* Variables and functions */
 int VLC_ENOMEM ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VOUT_WINDOW_TYPE_DUMMY ; 
 int /*<<< orphan*/  ops ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 void* var_InheritAddress (TYPE_2__*,char*) ; 
 TYPE_1__* vlc_obj_malloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int Open(vout_window_t *wnd)
{
    wextern_t *sys = vlc_obj_malloc(VLC_OBJECT(wnd), sizeof(*sys));
    if (unlikely(sys==NULL))
        return VLC_ENOMEM;
    sys->opaque          = var_InheritAddress( wnd, "vout-cb-opaque" );
    sys->setResizeCb     = var_InheritAddress( wnd, "vout-cb-resize-cb" );

    wnd->sys = sys;
    wnd->type = VOUT_WINDOW_TYPE_DUMMY;
    wnd->ops = &ops;
    return VLC_SUCCESS;
}