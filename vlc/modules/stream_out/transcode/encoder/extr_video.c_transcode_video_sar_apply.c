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
struct TYPE_4__ {int i_sar_num; int i_sar_den; int i_x_offset; int i_visible_width; int i_visible_height; int i_y_offset; } ;
typedef  TYPE_1__ video_format_t ;
typedef  int uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_ureduce (int*,int*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void transcode_video_sar_apply( const video_format_t *p_src,
                                       video_format_t *p_dst )
{
    /* Check whether a particular aspect ratio was requested */
    if( p_dst->i_sar_num <= 0 || p_dst->i_sar_den <= 0 )
    {
        vlc_ureduce( &p_dst->i_sar_num, &p_dst->i_sar_den,
                     (uint64_t)p_src->i_sar_num * (p_dst->i_x_offset + p_dst->i_visible_width)
                                                * (p_src->i_x_offset + p_src->i_visible_height),
                     (uint64_t)p_src->i_sar_den * (p_dst->i_y_offset + p_dst->i_visible_height)
                                                * (p_src->i_y_offset + p_src->i_visible_width),
                     0 );
    }
    else
    {
        vlc_ureduce( &p_dst->i_sar_num, &p_dst->i_sar_den,
                     p_dst->i_sar_num, p_dst->i_sar_den, 0 );
    }
}