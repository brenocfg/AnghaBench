#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_7__ ;
typedef  struct TYPE_14__   TYPE_6__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  video_format_t ;
struct TYPE_12__ {scalar_t__ x; scalar_t__ y; } ;
struct TYPE_10__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_14__ {int flags; TYPE_4__ extent; TYPE_2__ origin; } ;
struct TYPE_13__ {scalar_t__ i_next_update; TYPE_6__ region; } ;
typedef  TYPE_5__ subtext_updater_sys_t ;
typedef  TYPE_6__ substext_updater_region_t ;
struct TYPE_9__ {TYPE_5__* p_sys; } ;
struct TYPE_15__ {scalar_t__ i_original_picture_width; scalar_t__ i_original_picture_height; TYPE_3__* p_region; scalar_t__ b_absolute; TYPE_1__ updater; } ;
typedef  TYPE_7__ subpicture_t ;
struct TYPE_11__ {int /*<<< orphan*/  i_y; int /*<<< orphan*/  i_x; } ;

/* Variables and functions */
 int UPDT_REGION_EXTENT_X_IS_RATIO ; 
 int UPDT_REGION_EXTENT_Y_IS_RATIO ; 
 int UPDT_REGION_FIXED_DONE ; 
 int UPDT_REGION_ORIGIN_X_IS_RATIO ; 
 int UPDT_REGION_ORIGIN_Y_IS_RATIO ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int SubpictureTextValidate(subpicture_t *subpic,
                                  bool has_src_changed, const video_format_t *fmt_src,
                                  bool has_dst_changed, const video_format_t *fmt_dst,
                                  vlc_tick_t ts)
{
    subtext_updater_sys_t *sys = subpic->updater.p_sys;
    VLC_UNUSED(fmt_src); VLC_UNUSED(fmt_dst);

    if (!has_src_changed && !has_dst_changed &&
        (sys->i_next_update == VLC_TICK_INVALID || sys->i_next_update > ts))
        return VLC_SUCCESS;

    substext_updater_region_t *p_updtregion = &sys->region;

    if (!(p_updtregion->flags & UPDT_REGION_FIXED_DONE) &&
        subpic->b_absolute && subpic->p_region &&
        subpic->i_original_picture_width > 0 &&
        subpic->i_original_picture_height > 0)
    {
        p_updtregion->flags |= UPDT_REGION_FIXED_DONE;
        p_updtregion->origin.x = subpic->p_region->i_x;
        p_updtregion->origin.y = subpic->p_region->i_y;
        p_updtregion->extent.x = subpic->i_original_picture_width;
        p_updtregion->extent.y = subpic->i_original_picture_height;
        p_updtregion->flags &= ~(UPDT_REGION_ORIGIN_X_IS_RATIO|UPDT_REGION_ORIGIN_Y_IS_RATIO|
                                 UPDT_REGION_EXTENT_X_IS_RATIO|UPDT_REGION_EXTENT_Y_IS_RATIO);
    }

    return VLC_EGENERIC;
}