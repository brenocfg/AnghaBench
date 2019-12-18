#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int i_y_offset; int i_x_offset; int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_visible_width; } ;
struct TYPE_16__ {TYPE_2__ source; TYPE_6__* sys; } ;
typedef  TYPE_5__ vout_display_t ;
struct TYPE_14__ {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct TYPE_17__ {scalar_t__ dither; TYPE_3__ place; int /*<<< orphan*/  cv; } ;
typedef  TYPE_6__ vout_display_sys_t ;
typedef  int /*<<< orphan*/ * vlc_tick_t ;
typedef  int /*<<< orphan*/  subpicture_t ;
struct TYPE_12__ {int /*<<< orphan*/  i_bmask; int /*<<< orphan*/  i_gmask; int /*<<< orphan*/  i_rmask; } ;
struct TYPE_18__ {TYPE_4__* p; TYPE_1__ format; } ;
typedef  TYPE_7__ picture_t ;
struct TYPE_15__ {int i_pitch; int i_pixel_pitch; int /*<<< orphan*/ * p_pixels; } ;

/* Variables and functions */
 int /*<<< orphan*/  CUCUL_COLOR_BLACK ; 
 int /*<<< orphan*/  CUCUL_COLOR_DEFAULT ; 
 int /*<<< orphan*/  Manage (TYPE_5__*) ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cucul_clear_canvas (int /*<<< orphan*/ ) ; 
 scalar_t__ cucul_create_dither (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cucul_dither_bitmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cucul_set_color_ansi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_5__*,char*) ; 

__attribute__((used)) static void Prepare(vout_display_t *vd, picture_t *picture,
                    subpicture_t *subpicture, vlc_tick_t date)
{
    Manage(vd);
    VLC_UNUSED(date);

    vout_display_sys_t *sys = vd->sys;

    if (!sys->dither) {
        /* Create the libcaca dither object */
        sys->dither = cucul_create_dither(32,
                                            vd->source.i_visible_width,
                                            vd->source.i_visible_height,
                                            picture->p[0].i_pitch,
                                            picture->format.i_rmask,
                                            picture->format.i_gmask,
                                            picture->format.i_bmask,
                                            0x00000000);

        if (!sys->dither) {
            msg_Err(vd, "could not create libcaca dither object");
            return;
        }
    }

    cucul_set_color_ansi(sys->cv, CUCUL_COLOR_DEFAULT, CUCUL_COLOR_BLACK);
    cucul_clear_canvas(sys->cv);

    const int crop_offset = vd->source.i_y_offset * picture->p->i_pitch +
                            vd->source.i_x_offset * picture->p->i_pixel_pitch;
    cucul_dither_bitmap(sys->cv, sys->place.x, sys->place.y,
                        sys->place.width, sys->place.height,
                        sys->dither,
                        &picture->p->p_pixels[crop_offset]);
    VLC_UNUSED(subpicture);
}