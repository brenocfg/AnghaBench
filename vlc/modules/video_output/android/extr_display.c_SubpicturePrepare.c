#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_6__ ;
typedef  struct TYPE_23__   TYPE_5__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_20__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_display_t ;
struct TYPE_23__ {int left; int right; int top; int bottom; } ;
struct TYPE_21__ {scalar_t__ i_sub_last_order; int /*<<< orphan*/  p_spu_blend; TYPE_6__* p_sub_pic; int /*<<< orphan*/  p_sub_window; TYPE_5__ sub_last_region; } ;
typedef  TYPE_3__ vout_display_sys_t ;
struct TYPE_22__ {scalar_t__ i_order; } ;
typedef  TYPE_4__ subpicture_t ;
struct TYPE_24__ {TYPE_1__* p; } ;
struct TYPE_19__ {int i_pixel_pitch; int i_pitch; int /*<<< orphan*/ * p_pixels; } ;
typedef  TYPE_5__ ARect ;

/* Variables and functions */
 scalar_t__ AndroidWindow_LockPicture (TYPE_3__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int /*<<< orphan*/  SubtitleGetDirtyBounds (TYPE_2__*,TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  SubtitleRegionToBounds (TYPE_4__*,TYPE_5__*) ; 
 scalar_t__ memcmp (TYPE_5__*,TYPE_5__*,int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  picture_BlendSubpicture (TYPE_6__*,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void SubpicturePrepare(vout_display_t *vd, subpicture_t *subpicture)
{
    vout_display_sys_t *sys = vd->sys;
    ARect memset_bounds;

    SubtitleRegionToBounds(subpicture, &memset_bounds);

    if( subpicture )
    {
        if( subpicture->i_order == sys->i_sub_last_order
         && memcmp( &memset_bounds, &sys->sub_last_region, sizeof(ARect) ) == 0 )
            return;

        sys->i_sub_last_order = subpicture->i_order;
        sys->sub_last_region = memset_bounds;
    }

    if (AndroidWindow_LockPicture(sys, sys->p_sub_window, sys->p_sub_pic) != 0)
        return;

    /* Clear the subtitles surface. */
    SubtitleGetDirtyBounds(vd, subpicture, &memset_bounds);
    const int x_pixels_offset = memset_bounds.left
                                * sys->p_sub_pic->p[0].i_pixel_pitch;
    const int i_line_size = (memset_bounds.right - memset_bounds.left)
                            * sys->p_sub_pic->p->i_pixel_pitch;
    for (int y = memset_bounds.top; y < memset_bounds.bottom; y++)
        memset(&sys->p_sub_pic->p[0].p_pixels[y * sys->p_sub_pic->p[0].i_pitch
                                              + x_pixels_offset], 0, i_line_size);

    if (subpicture)
        picture_BlendSubpicture(sys->p_sub_pic, sys->p_spu_blend, subpicture);
}