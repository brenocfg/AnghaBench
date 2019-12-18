#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  xcb_void_cookie_t ;
typedef  int /*<<< orphan*/  xcb_shm_seg_t ;
struct TYPE_16__ {int /*<<< orphan*/  error_code; } ;
typedef  TYPE_3__ xcb_generic_error_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_17__ {TYPE_5__* sys; } ;
typedef  TYPE_4__ vout_display_t ;
struct TYPE_14__ {size_t i_y_offset; int /*<<< orphan*/  i_x_offset; int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_visible_width; } ;
struct TYPE_18__ {scalar_t__ attached; int /*<<< orphan*/  depth; TYPE_1__ fmt; int /*<<< orphan*/  gc; int /*<<< orphan*/  window; int /*<<< orphan*/ * conn; int /*<<< orphan*/  segment; } ;
typedef  TYPE_5__ vout_display_sys_t ;
struct TYPE_19__ {TYPE_2__* p; TYPE_7__* p_sys; } ;
typedef  TYPE_6__ picture_t ;
struct TYPE_20__ {int /*<<< orphan*/  offset; } ;
typedef  TYPE_7__ picture_buffer_t ;
struct TYPE_15__ {int i_pitch; int i_pixel_pitch; unsigned int i_lines; scalar_t__ p_pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  XCB_IMAGE_FORMAT_Z_PIXMAP ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_4__*,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_xcb_Manage (TYPE_4__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_put_image_checked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int const,scalar_t__) ; 
 TYPE_3__* xcb_request_check (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_shm_detach (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_shm_put_image_checked (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,unsigned int,int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Display (vout_display_t *vd, picture_t *pic)
{
    vout_display_sys_t *sys = vd->sys;
    xcb_connection_t *conn = sys->conn;
    const picture_buffer_t *buf = pic->p_sys;
    xcb_shm_seg_t segment = sys->segment;
    xcb_void_cookie_t ck;

    vlc_xcb_Manage(vd, sys->conn);

    if (sys->attached)
        ck = xcb_shm_put_image_checked(conn, sys->window, sys->gc,
              /* real width */ pic->p->i_pitch / pic->p->i_pixel_pitch,
             /* real height */ pic->p->i_lines,
                       /* x */ sys->fmt.i_x_offset,
                       /* y */ sys->fmt.i_y_offset,
                   /* width */ sys->fmt.i_visible_width,
                  /* height */ sys->fmt.i_visible_height,
                               0, 0, sys->depth, XCB_IMAGE_FORMAT_Z_PIXMAP,
                               0, segment, buf->offset);
    else {
        const size_t offset = sys->fmt.i_y_offset * pic->p->i_pitch;
        const unsigned lines = pic->p->i_lines - sys->fmt.i_y_offset;

        ck = xcb_put_image_checked(conn, XCB_IMAGE_FORMAT_Z_PIXMAP,
                               sys->window, sys->gc,
                               pic->p->i_pitch / pic->p->i_pixel_pitch,
                               lines, -sys->fmt.i_x_offset, 0, 0, sys->depth,
                               pic->p->i_pitch * lines,
                               pic->p->p_pixels + offset);
    }

    /* Wait for reply. This makes sure that the X server gets CPU time to
     * display the picture. xcb_flush() is *not* sufficient: especially
     * with shared memory the PUT requests are so short that many of them
     * can fit in X11 socket output buffer before the kernel preempts VLC.
     */
   xcb_generic_error_t *e = xcb_request_check(conn, ck);
   if (e != NULL) {
       msg_Err(vd, "%s: X11 error %d", "cannot put image", e->error_code);
       free(e);
   }

    /* FIXME might be WAY better to wait in some case (be carefull with
     * VOUT_DISPLAY_RESET_PICTURES if done) + does not work with
     * vout_display wrapper. */

    if (sys->attached)
        xcb_shm_detach(conn, segment);
}