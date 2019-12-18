#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int i_visible_height; unsigned int i_sar_den; unsigned int i_sar_num; unsigned int i_visible_width; } ;
typedef  TYPE_1__ video_format_t ;
typedef  unsigned int uint64_t ;

/* Variables and functions */

__attribute__((used)) static void VoutDisplayCropRatio(int *left, int *top, int *right, int *bottom,
                                 const video_format_t *source,
                                 unsigned num, unsigned den)
{
    unsigned scaled_width  = (uint64_t)source->i_visible_height * num * source->i_sar_den / den / source->i_sar_num;
    unsigned scaled_height = (uint64_t)source->i_visible_width  * den * source->i_sar_num / num / source->i_sar_den;

    if (scaled_width < source->i_visible_width) {
        *left   = (source->i_visible_width - scaled_width) / 2;
        *top    = 0;
        *right  = *left + scaled_width;
        *bottom = *top  + source->i_visible_height;
    } else {
        *left   = 0;
        *top    = (source->i_visible_height - scaled_height) / 2;
        *right  = *left + source->i_visible_width;
        *bottom = *top  + scaled_height;
    }
}