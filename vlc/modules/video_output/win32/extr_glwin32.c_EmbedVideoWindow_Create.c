#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  hwnd; } ;
struct TYPE_12__ {int /*<<< orphan*/ * ops; TYPE_1__ handle; int /*<<< orphan*/  type; } ;
typedef  TYPE_3__ vout_window_t ;
struct TYPE_13__ {TYPE_5__* sys; } ;
typedef  TYPE_4__ vout_display_t ;
struct TYPE_11__ {int /*<<< orphan*/  hvideownd; } ;
struct TYPE_14__ {TYPE_2__ sys; } ;
typedef  TYPE_5__ vout_display_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  VOUT_WINDOW_TYPE_HWND ; 
 int /*<<< orphan*/  embedVideoWindow_Ops ; 
 TYPE_3__* vlc_object_create (TYPE_4__*,int) ; 

__attribute__((used)) static vout_window_t *EmbedVideoWindow_Create(vout_display_t *vd)
{
    vout_display_sys_t *sys = vd->sys;

    vout_window_t *wnd = vlc_object_create(vd, sizeof(vout_window_t));
    if (!wnd)
        return NULL;

    wnd->type = VOUT_WINDOW_TYPE_HWND;
    wnd->handle.hwnd = sys->sys.hvideownd;
    wnd->ops = &embedVideoWindow_Ops;
    return wnd;
}