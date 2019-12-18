#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_void_cookie_t ;
struct TYPE_15__ {int /*<<< orphan*/  error_code; } ;
typedef  TYPE_4__ xcb_generic_error_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_16__ {TYPE_3__* cfg; TYPE_6__* sys; } ;
typedef  TYPE_5__ vout_display_t ;
struct TYPE_12__ {int /*<<< orphan*/  dest; int /*<<< orphan*/  scale; } ;
struct TYPE_17__ {TYPE_1__ picture; int /*<<< orphan*/ * conn; } ;
typedef  TYPE_6__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  picture_t ;
struct TYPE_13__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_14__ {TYPE_2__ display; } ;

/* Variables and functions */
 int /*<<< orphan*/  XCB_RENDER_PICTURE_NONE ; 
 int /*<<< orphan*/  XCB_RENDER_PICT_OP_SRC ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_5__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_xcb_Manage (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_render_composite_checked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_4__* xcb_request_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Display(vout_display_t *vd, picture_t *pic)
{
    vout_display_sys_t *sys = vd->sys;
    xcb_connection_t *conn = sys->conn;
    xcb_void_cookie_t ck;

    vlc_xcb_Manage(vd, conn);

    /* Copy the scaled picture into the target picture, in other words
     * copy the rendered pixmap into the window.
     */
    ck = xcb_render_composite_checked(conn, XCB_RENDER_PICT_OP_SRC,
                                      sys->picture.scale,
                                      XCB_RENDER_PICTURE_NONE,
                                      sys->picture.dest, 0, 0, 0, 0, 0, 0,
                                      vd->cfg->display.width,
                                      vd->cfg->display.height);

    xcb_generic_error_t *e = xcb_request_check(conn, ck);
    if (e != NULL) { /* Not all errors will be detected here. */
        msg_Dbg(vd, "%s: RENDER error %d", "cannot composite",
                e->error_code);
        free(e);
    }
    (void) pic;
}