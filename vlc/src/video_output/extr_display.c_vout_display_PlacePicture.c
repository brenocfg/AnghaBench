#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {unsigned int width; unsigned int height; unsigned int x; unsigned int y; } ;
typedef  TYPE_4__ vout_display_place_t ;
struct TYPE_15__ {unsigned int num; unsigned int const den; } ;
struct TYPE_17__ {unsigned int width; unsigned int height; TYPE_1__ sar; } ;
struct TYPE_16__ {int horizontal; int vertical; } ;
struct TYPE_19__ {TYPE_3__ display; TYPE_2__ align; scalar_t__ is_display_filled; } ;
typedef  TYPE_5__ vout_display_cfg_t ;
struct TYPE_20__ {unsigned int i_visible_width; unsigned int i_visible_height; unsigned int i_sar_den; unsigned int const i_sar_num; scalar_t__ projection_mode; } ;
typedef  TYPE_6__ video_format_t ;
typedef  unsigned int int64_t ;

/* Variables and functions */
 scalar_t__ PROJECTION_MODE_RECTANGULAR ; 
#define  VLC_VIDEO_ALIGN_BOTTOM 131 
#define  VLC_VIDEO_ALIGN_LEFT 130 
#define  VLC_VIDEO_ALIGN_RIGHT 129 
#define  VLC_VIDEO_ALIGN_TOP 128 
 int /*<<< orphan*/  memset (TYPE_4__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  video_format_ApplyRotation (TYPE_6__*,TYPE_6__ const*) ; 
 int /*<<< orphan*/  vout_display_GetDefaultDisplaySize (unsigned int*,unsigned int*,TYPE_6__ const*,TYPE_5__*) ; 

void vout_display_PlacePicture(vout_display_place_t *place,
                               const video_format_t *source,
                               const vout_display_cfg_t *cfg)
{
    /* */
    memset(place, 0, sizeof(*place));
    if (cfg->display.width == 0 || cfg->display.height == 0)
        return;

    /* */
    unsigned display_width;
    unsigned display_height;

    video_format_t source_rot;
    video_format_ApplyRotation(&source_rot, source);
    source = &source_rot;

    if (cfg->is_display_filled) {
        display_width  = cfg->display.width;
        display_height = cfg->display.height;
    } else {
        vout_display_cfg_t cfg_tmp = *cfg;

        cfg_tmp.display.width  = 0;
        cfg_tmp.display.height = 0;
        vout_display_GetDefaultDisplaySize(&display_width, &display_height,
                                           source, &cfg_tmp);
    }

    const unsigned width  = source->i_visible_width;
    const unsigned height = source->i_visible_height;
    /* Compute the height if we use the width to fill up display_width */
    const int64_t scaled_height = (int64_t)height * display_width  * cfg->display.sar.num * source->i_sar_den / (width  * source->i_sar_num * cfg->display.sar.den);
    /* And the same but switching width/height */
    const int64_t scaled_width  = (int64_t)width  * display_height * cfg->display.sar.den * source->i_sar_num / (height * source->i_sar_den * cfg->display.sar.num);

    if (source->projection_mode == PROJECTION_MODE_RECTANGULAR) {
        /* We keep the solution that avoid filling outside the display */
        if (scaled_width <= cfg->display.width) {
            place->width  = scaled_width;
            place->height = display_height;
        } else {
            place->width  = display_width;
            place->height = scaled_height;
        }
    } else {
        /* No need to preserve an aspect ratio for 360 video.
         * They can fill the display. */
        place->width  = display_width;
        place->height = display_height;
    }

    /*  Compute position */
    switch (cfg->align.horizontal) {
    case VLC_VIDEO_ALIGN_LEFT:
        place->x = 0;
        break;
    case VLC_VIDEO_ALIGN_RIGHT:
        place->x = cfg->display.width - place->width;
        break;
    default:
        place->x = ((int)cfg->display.width - (int)place->width) / 2;
        break;
    }

    switch (cfg->align.vertical) {
    case VLC_VIDEO_ALIGN_TOP:
        place->y = 0;
        break;
    case VLC_VIDEO_ALIGN_BOTTOM:
        place->y = cfg->display.height - place->height;
        break;
    default:
        place->y = ((int)cfg->display.height - (int)place->height) / 2;
        break;
    }
}