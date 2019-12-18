#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int /*<<< orphan*/ * event; } ;
typedef  TYPE_2__ vout_display_sys_win32_t ;
struct TYPE_16__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_3__ vout_display_place_t ;
struct TYPE_14__ {scalar_t__ vertical; } ;
struct TYPE_17__ {TYPE_1__ align; } ;
typedef  TYPE_4__ vout_display_cfg_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_19__ {int /*<<< orphan*/  i_height; int /*<<< orphan*/  i_width; int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_visible_width; int /*<<< orphan*/  i_y_offset; int /*<<< orphan*/  i_x_offset; } ;
struct TYPE_18__ {int place_changed; TYPE_3__ place; TYPE_7__ texture_source; TYPE_4__ vdcfg; } ;
typedef  TYPE_5__ display_win32_area_t ;

/* Variables and functions */
 int /*<<< orphan*/  CommonChangeThumbnailClip (int /*<<< orphan*/ *,TYPE_2__*,int) ; 
 scalar_t__ VLC_VIDEO_ALIGN_BOTTOM ; 
 scalar_t__ VLC_VIDEO_ALIGN_TOP ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  vout_display_PlaceEquals (TYPE_3__*,TYPE_3__*) ; 
 int /*<<< orphan*/  vout_display_PlacePicture (TYPE_3__*,TYPE_7__*,TYPE_4__*) ; 

void CommonPlacePicture(vlc_object_t *obj, display_win32_area_t *area, vout_display_sys_win32_t *sys)
{
    /* Update the window position and size */
    vout_display_cfg_t place_cfg = area->vdcfg;

#if (defined(MODULE_NAME_IS_glwin32))
    /* Reverse vertical alignment as the GL tex are Y inverted */
    if (place_cfg.align.vertical == VLC_VIDEO_ALIGN_TOP)
        place_cfg.align.vertical = VLC_VIDEO_ALIGN_BOTTOM;
    else if (place_cfg.align.vertical == VLC_VIDEO_ALIGN_BOTTOM)
        place_cfg.align.vertical = VLC_VIDEO_ALIGN_TOP;
#endif

    vout_display_place_t before_place = area->place;
    vout_display_PlacePicture(&area->place, &area->texture_source, &place_cfg);

    /* Signal the change in size/position */
    if (!vout_display_PlaceEquals(&before_place, &area->place))
    {
        area->place_changed |= true;

#ifndef NDEBUG
        msg_Dbg(obj, "UpdateRects source offset: %i,%i visible: %ix%i decoded: %ix%i",
            area->texture_source.i_x_offset, area->texture_source.i_y_offset,
            area->texture_source.i_visible_width, area->texture_source.i_visible_height,
            area->texture_source.i_width, area->texture_source.i_height);
        msg_Dbg(obj, "UpdateRects image_dst coords: %i,%i %ix%i",
            area->place.x, area->place.y, area->place.width, area->place.height);
#endif

#if !VLC_WINSTORE_APP
        if (sys->event != NULL)
        {
            CommonChangeThumbnailClip(obj, sys, true);
        }
#endif
    }
}