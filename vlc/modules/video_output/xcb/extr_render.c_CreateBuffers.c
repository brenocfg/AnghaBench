#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_26__   TYPE_9__ ;
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;
typedef  struct TYPE_17__   TYPE_10__ ;

/* Type definitions */
struct TYPE_22__ {int member_8; int matrix12; int matrix21; int matrix11; int matrix22; int /*<<< orphan*/  member_7; int /*<<< orphan*/  member_6; int /*<<< orphan*/  member_5; int /*<<< orphan*/  member_4; int /*<<< orphan*/  member_3; int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_5__ xcb_render_transform_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct TYPE_17__ {int i_visible_width; int i_visible_height; int orientation; } ;
struct TYPE_23__ {TYPE_7__* sys; TYPE_10__ source; } ;
typedef  TYPE_6__ vout_display_t ;
struct TYPE_21__ {int /*<<< orphan*/  crop; int /*<<< orphan*/  scale; } ;
struct TYPE_25__ {int height; int width; } ;
struct TYPE_20__ {int /*<<< orphan*/  argb; } ;
struct TYPE_19__ {int /*<<< orphan*/  scale; int /*<<< orphan*/  crop; } ;
struct TYPE_24__ {int src_x; int src_y; int /*<<< orphan*/ * filter; TYPE_4__ picture; TYPE_8__ place; TYPE_3__ format; TYPE_2__ drawable; int /*<<< orphan*/  root; int /*<<< orphan*/ * conn; } ;
typedef  TYPE_7__ vout_display_sys_t ;
typedef  TYPE_8__ vout_display_place_t ;
struct TYPE_18__ {int width; int height; } ;
struct TYPE_26__ {TYPE_1__ display; } ;
typedef  TYPE_9__ vout_display_cfg_t ;
typedef  TYPE_10__ video_format_t ;
typedef  int int32_t ;

/* Variables and functions */
#define  ORIENT_BOTTOM_LEFT 135 
#define  ORIENT_BOTTOM_RIGHT 134 
 scalar_t__ ORIENT_IS_SWAP (int) ; 
#define  ORIENT_LEFT_BOTTOM 133 
#define  ORIENT_LEFT_TOP 132 
#define  ORIENT_RIGHT_BOTTOM 131 
#define  ORIENT_RIGHT_TOP 130 
#define  ORIENT_TOP_LEFT 129 
#define  ORIENT_TOP_RIGHT 128 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_display_PlacePicture (TYPE_8__*,TYPE_10__ const*,TYPE_9__ const*) ; 
 int /*<<< orphan*/  xcb_create_pixmap (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  xcb_render_create_picture (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_render_set_picture_filter (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_render_set_picture_transform (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_5__) ; 

__attribute__((used)) static void CreateBuffers(vout_display_t *vd, const vout_display_cfg_t *cfg)
{
    const video_format_t *fmt = &vd->source;
    vout_display_sys_t *sys = vd->sys;
    xcb_connection_t *conn = sys->conn;

    xcb_create_pixmap(conn, 32, sys->drawable.crop, sys->root,
                      fmt->i_visible_width, fmt->i_visible_height);
    xcb_create_pixmap(conn, 32, sys->drawable.scale, sys->root,
                      cfg->display.width, cfg->display.height);
    xcb_render_create_picture(conn, sys->picture.crop, sys->drawable.crop,
                              sys->format.argb, 0, NULL);
    xcb_render_create_picture(conn, sys->picture.scale, sys->drawable.scale,
                              sys->format.argb, 0, NULL);

    vout_display_place_t *place = &sys->place;
    vout_display_PlacePicture(place, fmt, cfg);

    /* Homogeneous coordinates transform from destination(place)
     * to source(fmt) */
    int32_t ax = place->height; /* multiply x instead of dividing y */
    int32_t ay = place->width; /* multiply y instead of dividing x */
    int32_t bx = 0;
    int32_t by = 0;

    switch (fmt->orientation) {
        case ORIENT_TOP_LEFT:
        case ORIENT_LEFT_TOP:
            break;
        case ORIENT_TOP_RIGHT:
        case ORIENT_RIGHT_TOP:
            ax *= -1;
            bx -= place->width;
            break;
        case ORIENT_BOTTOM_LEFT:
        case ORIENT_LEFT_BOTTOM:
            ay *= -1;
            by -= place->height;
            break;
        case ORIENT_BOTTOM_RIGHT:
        case ORIENT_RIGHT_BOTTOM:
            ax *= -1;
            ay *= -1;
            bx -= place->width;
            by -= place->height;
            break;
    }

    sys->src_x = bx;
    sys->src_y = by;

    xcb_render_transform_t transform = {
        0, 0, 0,
        0, 0, 0,
        /* Multiply z by width and height to compensate for x and y above */
        0, 0, place->width * place->height,
    };

    if (ORIENT_IS_SWAP(fmt->orientation)) {
        transform.matrix12 = ay * fmt->i_visible_width;
        transform.matrix21 = ax * fmt->i_visible_height;
    } else {
        transform.matrix11 = ax * fmt->i_visible_width;
        transform.matrix22 = ay * fmt->i_visible_height;
    }

    xcb_render_set_picture_transform(conn, sys->picture.crop, transform);

    if (likely(sys->filter != NULL))
        xcb_render_set_picture_filter(conn, sys->picture.crop,
                                      strlen(sys->filter), sys->filter,
                                      0, NULL);
}