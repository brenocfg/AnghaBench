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
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_6__ {int /*<<< orphan*/  x11; } ;
struct TYPE_7__ {TYPE_1__ display; TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_window_t ;
struct TYPE_8__ {int /*<<< orphan*/  thread; int /*<<< orphan*/ * conn; } ;
typedef  TYPE_3__ vout_window_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  DeinitKeyboardExtension (TYPE_2__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_disconnect (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close (vout_window_t *wnd)
{
    vout_window_sys_t *p_sys = wnd->sys;
    xcb_connection_t *conn = p_sys->conn;

    vlc_cancel (p_sys->thread);
    vlc_join (p_sys->thread, NULL);

    DeinitKeyboardExtension(wnd);
    xcb_disconnect (conn);
    free (wnd->display.x11);
}