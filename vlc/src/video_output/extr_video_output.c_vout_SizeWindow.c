#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_9__ ;
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_8__* p; } ;
typedef  TYPE_7__ vout_thread_t ;
struct TYPE_15__ {unsigned int right; unsigned int left; unsigned int bottom; unsigned int top; } ;
struct TYPE_14__ {unsigned int width; unsigned int height; } ;
struct TYPE_13__ {unsigned int num; unsigned int den; } ;
struct TYPE_16__ {int mode; TYPE_4__ border; TYPE_3__ window; TYPE_2__ ratio; } ;
struct TYPE_12__ {unsigned int num; unsigned int den; } ;
struct TYPE_17__ {TYPE_5__ crop; TYPE_1__ dar; } ;
struct TYPE_19__ {int /*<<< orphan*/  display_cfg; TYPE_6__ source; } ;
typedef  TYPE_8__ vout_thread_sys_t ;
struct TYPE_20__ {unsigned int i_visible_width; unsigned int i_visible_height; unsigned int i_sar_num; int /*<<< orphan*/  orientation; } ;
typedef  TYPE_9__ video_format_t ;

/* Variables and functions */
#define  VOUT_CROP_BORDER 131 
#define  VOUT_CROP_NONE 130 
#define  VOUT_CROP_RATIO 129 
#define  VOUT_CROP_WINDOW 128 
 int /*<<< orphan*/  vlc_ureduce (unsigned int*,unsigned int*,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vout_display_SizeWindow (unsigned int*,unsigned int*,unsigned int,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vout_SizeWindow(vout_thread_t *vout,
                            const video_format_t *original,
                            unsigned *restrict width,
                            unsigned *restrict height)
{
    vout_thread_sys_t *sys = vout->p;
    unsigned w = original->i_visible_width;
    unsigned h = original->i_visible_height;
    unsigned sar_num = original->i_sar_num;
    unsigned sar_den = original->i_sar_num;

    switch (sys->source.crop.mode) {
        case VOUT_CROP_NONE:
            if (sys->source.dar.num > 0 && sys->source.dar.den > 0) {
                unsigned num = sys->source.dar.num * h;
                unsigned den = sys->source.dar.den * w;

                vlc_ureduce(&sar_num, &sar_den, num, den, 0);
            }
            break;

        case VOUT_CROP_RATIO: {
            unsigned num = sys->source.crop.ratio.num;
            unsigned den = sys->source.crop.ratio.den;

            if (w * den > h * num)
                w = h * num / den;
            else
                h = w * den / num;
            break;
        }

        case VOUT_CROP_WINDOW:
            w = sys->source.crop.window.width;
            h = sys->source.crop.window.height;
            break;

        case VOUT_CROP_BORDER:
            w = sys->source.crop.border.right - sys->source.crop.border.left;
            h = sys->source.crop.border.bottom - sys->source.crop.border.top;
            break;
    }

    /* If the vout thread is running, the window lock must be held here. */
    vout_display_SizeWindow(width, height, w, h, sar_num, sar_den,
                            original->orientation,
                            &sys->display_cfg);
}