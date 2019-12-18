#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {TYPE_2__* p_window; } ;
typedef  TYPE_3__ vout_display_sys_t ;
struct TYPE_14__ {int pixel_size; } ;
typedef  TYPE_4__ vlc_chroma_description_t ;
struct TYPE_11__ {unsigned int i_width; int /*<<< orphan*/  i_chroma; } ;
struct TYPE_15__ {unsigned int i_pic_count; TYPE_1__ fmt; int /*<<< orphan*/  b_opaque; } ;
typedef  TYPE_5__ android_window ;
struct TYPE_12__ {int i_pic_count; } ;

/* Variables and functions */
 scalar_t__ AndroidWindow_SetupANW (TYPE_3__*,TYPE_5__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__* vlc_fourcc_GetChromaDescription (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int AndroidWindow_Setup(vout_display_sys_t *sys,
                               android_window *p_window,
                               unsigned int i_pic_count)
{
    if (i_pic_count != 0)
        p_window->i_pic_count = i_pic_count;

    if (!p_window->b_opaque) {
        const vlc_chroma_description_t *p_dsc =
            vlc_fourcc_GetChromaDescription( p_window->fmt.i_chroma );
        if (p_dsc)
        {
            assert(p_dsc->pixel_size != 0);
            // For RGB (32 or 16) we need to align on 8 or 4 pixels, 16 pixels for YUV
            unsigned align_pixels = (16 / p_dsc->pixel_size) - 1;
            p_window->fmt.i_width = (p_window->fmt.i_width + align_pixels) & ~align_pixels;
        }

        if (AndroidWindow_SetupANW(sys, p_window) != 0)
            return -1;
    } else {
        sys->p_window->i_pic_count = 31; // TODO
    }

    return 0;
}