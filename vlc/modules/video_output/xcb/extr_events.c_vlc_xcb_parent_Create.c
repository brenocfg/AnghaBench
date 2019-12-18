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
typedef  int /*<<< orphan*/  xcb_screen_t ;
struct TYPE_12__ {int /*<<< orphan*/  root; } ;
typedef  TYPE_3__ xcb_get_geometry_reply_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_11__ {int /*<<< orphan*/  xid; } ;
struct TYPE_10__ {int /*<<< orphan*/  x11; } ;
struct TYPE_13__ {scalar_t__ type; TYPE_2__ handle; TYPE_1__ display; } ;
typedef  TYPE_4__ vout_window_t ;
typedef  int /*<<< orphan*/  vout_display_t ;
struct TYPE_14__ {TYPE_4__* window; } ;
typedef  TYPE_5__ vout_display_cfg_t ;

/* Variables and functions */
 int /*<<< orphan*/ * Connect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * FindScreen (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ *) ; 
 scalar_t__ VOUT_WINDOW_TYPE_XID ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  xcb_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_get_geometry (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_3__* xcb_get_geometry_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

vout_window_t *vlc_xcb_parent_Create(vout_display_t *vd,
                                     const vout_display_cfg_t *cfg,
                                     xcb_connection_t **restrict pconn,
                                     const xcb_screen_t **restrict pscreen)
{
    if (cfg->window->type != VOUT_WINDOW_TYPE_XID)
    {
        msg_Err (vd, "window not available");
        return NULL;
    }
    vout_window_t *wnd = cfg->window;

    xcb_connection_t *conn = Connect (VLC_OBJECT(vd), wnd->display.x11);
    if (conn == NULL)
        goto error;
    *pconn = conn;

    xcb_get_geometry_reply_t *geo =
        xcb_get_geometry_reply (conn, xcb_get_geometry (conn, wnd->handle.xid),
                                NULL);
    if (geo == NULL)
    {
        msg_Err (vd, "window not valid");
        goto error;
    }

    const xcb_screen_t *screen = FindScreen (VLC_OBJECT(vd), conn, geo->root);
    free (geo);
    if (screen == NULL)
        goto error;
    *pscreen = screen;
    return wnd;

error:
    if (conn != NULL)
        xcb_disconnect (conn);
    return NULL;
}