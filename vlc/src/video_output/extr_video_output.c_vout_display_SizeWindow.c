#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int num; unsigned int den; } ;
struct TYPE_6__ {unsigned int num; unsigned int den; } ;
struct TYPE_7__ {unsigned int width; unsigned int height; TYPE_1__ sar; } ;
struct TYPE_9__ {TYPE_3__ zoom; TYPE_2__ display; } ;
typedef  TYPE_4__ vout_display_cfg_t ;
typedef  int /*<<< orphan*/  video_orientation_t ;

/* Variables and functions */
 scalar_t__ ORIENT_IS_SWAP (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void vout_display_SizeWindow(unsigned *restrict width,
                                    unsigned *restrict height,
                                    unsigned w, unsigned h,
                                    unsigned sar_num, unsigned sar_den,
                                    video_orientation_t orientation,
                                    const vout_display_cfg_t *restrict cfg)
{
    *width = cfg->display.width;
    *height = cfg->display.height;

    /* If both width and height are forced, keep them as is. */
    if (*width != 0 && *height != 0)
        return;

    /* Compute intended video resolution from source. */
    assert(sar_num > 0 && sar_den > 0);
    w = (w * sar_num) / sar_den;

    /* Adjust video size for orientation and pixel A/R. */
    if (ORIENT_IS_SWAP(orientation)) {
        unsigned x = w;

        w = h;
        h = x;
    }

    if (cfg->display.sar.num > 0 && cfg->display.sar.den > 0)
        w = (w * cfg->display.sar.den) / cfg->display.sar.num;

    /* If width is forced, adjust height according to the aspect ratio */
    if (*width != 0) {
        *height = (*width * h) / w;
        return;
    }

    /* If height is forced, adjust width according to the aspect ratio */
    if (*height != 0) {
        *width = (*height * w) / h;
        return;
    }

    /* If neither width nor height are forced, use the requested zoom. */
    *width = (w * cfg->zoom.num) / cfg->zoom.den;
    *height = (h * cfg->zoom.num) / cfg->zoom.den;
}