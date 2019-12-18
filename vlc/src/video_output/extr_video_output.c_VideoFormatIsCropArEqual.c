#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int i_sar_num; int i_sar_den; scalar_t__ i_x_offset; scalar_t__ i_y_offset; scalar_t__ i_visible_width; scalar_t__ i_visible_height; } ;
typedef  TYPE_1__ video_format_t ;

/* Variables and functions */

__attribute__((used)) static bool VideoFormatIsCropArEqual(video_format_t *dst,
                                     const video_format_t *src)
{
    return dst->i_sar_num * src->i_sar_den == dst->i_sar_den * src->i_sar_num &&
           dst->i_x_offset       == src->i_x_offset &&
           dst->i_y_offset       == src->i_y_offset &&
           dst->i_visible_width  == src->i_visible_width &&
           dst->i_visible_height == src->i_visible_height;
}