#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int i_height; int i_visible_height; int i_y_offset; int i_sar_den; int i_frame_rate; } ;
typedef  TYPE_2__ video_format_t ;
struct TYPE_5__ {scalar_t__ b_double_rate; scalar_t__ b_half_height; } ;
struct deinterlace_ctx {TYPE_1__ settings; } ;

/* Variables and functions */

void GetDeinterlacingOutput( const struct deinterlace_ctx *p_context,
                             video_format_t *p_dst, const video_format_t *p_src )
{
    *p_dst = *p_src;

    if( p_context->settings.b_half_height )
    {
        p_dst->i_height /= 2;
        p_dst->i_visible_height /= 2;
        p_dst->i_y_offset /= 2;
        p_dst->i_sar_den *= 2;
    }

    if( p_context->settings.b_double_rate )
    {
        p_dst->i_frame_rate *= 2;
    }
}