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
struct TYPE_4__ {int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_visible_width; int /*<<< orphan*/  i_y_offset; int /*<<< orphan*/  i_x_offset; } ;
typedef  TYPE_1__ video_format_t ;

/* Variables and functions */

void video_format_CopyCrop( video_format_t *p_dst, const video_format_t *p_src )
{
    p_dst->i_x_offset       = p_src->i_x_offset;
    p_dst->i_y_offset       = p_src->i_y_offset;
    p_dst->i_visible_width  = p_src->i_visible_width;
    p_dst->i_visible_height = p_src->i_visible_height;
}