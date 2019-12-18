#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_40__   TYPE_9__ ;
typedef  struct TYPE_39__   TYPE_8__ ;
typedef  struct TYPE_38__   TYPE_7__ ;
typedef  struct TYPE_37__   TYPE_6__ ;
typedef  struct TYPE_36__   TYPE_5__ ;
typedef  struct TYPE_35__   TYPE_4__ ;
typedef  struct TYPE_34__   TYPE_3__ ;
typedef  struct TYPE_33__   TYPE_2__ ;
typedef  struct TYPE_32__   TYPE_1__ ;
typedef  struct TYPE_31__   TYPE_14__ ;
typedef  struct TYPE_30__   TYPE_13__ ;
typedef  struct TYPE_29__   TYPE_12__ ;
typedef  struct TYPE_28__   TYPE_11__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
struct TYPE_38__ {int member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_7__ xcb_render_color_t ;
struct TYPE_39__ {int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_8__ xcb_rectangle_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_28__ {int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_visible_width; int /*<<< orphan*/  i_y_offset; int /*<<< orphan*/  i_x_offset; } ;
struct TYPE_40__ {TYPE_4__* cfg; TYPE_10__* sys; TYPE_11__ source; } ;
typedef  TYPE_9__ vout_display_t ;
struct TYPE_37__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_36__ {int /*<<< orphan*/  scale; int /*<<< orphan*/  crop; int /*<<< orphan*/  source; } ;
struct TYPE_32__ {int /*<<< orphan*/  source; } ;
struct TYPE_27__ {TYPE_6__ place; int /*<<< orphan*/  src_y; int /*<<< orphan*/  src_x; TYPE_5__ picture; int /*<<< orphan*/  gc; TYPE_1__ drawable; int /*<<< orphan*/  segment; int /*<<< orphan*/ * conn; } ;
typedef  TYPE_10__ vout_display_sys_t ;
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  TYPE_11__ video_format_t ;
struct TYPE_29__ {TYPE_13__* p_region; } ;
typedef  TYPE_12__ subpicture_t ;
struct TYPE_30__ {struct TYPE_30__* p_next; } ;
typedef  TYPE_13__ subpicture_region_t ;
struct TYPE_31__ {TYPE_2__* p; } ;
typedef  TYPE_14__ picture_t ;
struct TYPE_34__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; } ;
struct TYPE_35__ {TYPE_3__ display; } ;
struct TYPE_33__ {int i_pitch; int i_pixel_pitch; int i_lines; int /*<<< orphan*/  p_pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (TYPE_8__*) ; 
 size_t PictureAttach (TYPE_9__*,TYPE_14__*) ; 
 int /*<<< orphan*/  PictureDetach (TYPE_9__*) ; 
 int /*<<< orphan*/  RenderRegion (TYPE_9__*,TYPE_12__*,TYPE_13__*) ; 
 int /*<<< orphan*/  XCB_IMAGE_FORMAT_Z_PIXMAP ; 
 int /*<<< orphan*/  XCB_RENDER_PICTURE_NONE ; 
 int /*<<< orphan*/  XCB_RENDER_PICT_OP_SRC ; 
 int /*<<< orphan*/  xcb_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_put_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_render_composite (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xcb_render_fill_rectangles (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_7__ const,int /*<<< orphan*/ ,TYPE_8__*) ; 
 int /*<<< orphan*/  xcb_shm_put_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void Prepare(vout_display_t *vd, picture_t *pic, subpicture_t *subpic,
                    vlc_tick_t date)
{
    const video_format_t *fmt = &vd->source;
    vout_display_sys_t *sys = vd->sys;
    xcb_connection_t *conn = sys->conn;

    size_t offset = PictureAttach(vd, pic);
    if (offset != (size_t)-1) {
        xcb_shm_put_image(conn, sys->drawable.source, sys->gc,
                          pic->p->i_pitch / pic->p->i_pixel_pitch,
                          pic->p->i_lines, 0, 0,
                          pic->p->i_pitch / pic->p->i_pixel_pitch,
                          pic->p->i_lines, 0, 0, 32, XCB_IMAGE_FORMAT_Z_PIXMAP,
                          0, sys->segment, offset);
    } else {
        xcb_put_image(conn, XCB_IMAGE_FORMAT_Z_PIXMAP, sys->drawable.source,
                      sys->gc, pic->p->i_pitch / pic->p->i_pixel_pitch,
                      pic->p->i_lines, 0, 0, 0, 32,
                      pic->p->i_pitch * pic->p->i_lines, pic->p->p_pixels);
    }

    /* Crop the picture with pixel accuracy */
    xcb_render_composite(conn, XCB_RENDER_PICT_OP_SRC,
                         sys->picture.source, XCB_RENDER_PICTURE_NONE,
                         sys->picture.crop,
                         fmt->i_x_offset, fmt->i_y_offset, 0, 0,
                         0, 0, fmt->i_visible_width, fmt->i_visible_height);

    /* Blank background */
    static const xcb_render_color_t black_color = { 0, 0, 0, 0xffff };
    xcb_rectangle_t rects[] = {
        { 0, 0, vd->cfg->display.width, vd->cfg->display.height },
    };

    xcb_render_fill_rectangles(conn, XCB_RENDER_PICT_OP_SRC,
                               sys->picture.scale, black_color,
                               ARRAY_SIZE(rects), rects);

    /* Scale and orient the picture */
    xcb_render_composite(conn, XCB_RENDER_PICT_OP_SRC,
                         sys->picture.crop, XCB_RENDER_PICTURE_NONE,
                         sys->picture.scale, sys->src_x, sys->src_y, 0, 0,
                         sys->place.x, sys->place.y,
                         sys->place.width, sys->place.height);
    if (offset != (size_t)-1)
        PictureDetach(vd);

    /* Blend subpictures */
    if (subpic != NULL)
        for (subpicture_region_t *r = subpic->p_region; r != NULL;
             r = r->p_next)
            RenderRegion(vd, subpic, r);

    xcb_flush(conn);
    (void) date;
}