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
struct TYPE_4__ {scalar_t__ i_frame_rate_base; scalar_t__ i_frame_rate; } ;
typedef  TYPE_1__ video_format_t ;

/* Variables and functions */
 scalar_t__ ENC_FRAMERATE ; 
 scalar_t__ ENC_FRAMERATE_BASE ; 
 int /*<<< orphan*/  vlc_ureduce (scalar_t__*,scalar_t__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void transcode_video_framerate_apply( const video_format_t *p_src,
                                             video_format_t *p_dst )
{
    /* Handle frame rate conversion */
    if( !p_dst->i_frame_rate || !p_dst->i_frame_rate_base )
    {
        p_dst->i_frame_rate = p_src->i_frame_rate;
        p_dst->i_frame_rate_base = p_src->i_frame_rate_base;

        if( !p_dst->i_frame_rate || !p_dst->i_frame_rate_base )
        {
            /* Pick a sensible default value */
            p_dst->i_frame_rate = ENC_FRAMERATE;
            p_dst->i_frame_rate_base = ENC_FRAMERATE_BASE;
        }
    }

    vlc_ureduce( &p_dst->i_frame_rate, &p_dst->i_frame_rate_base,
                  p_dst->i_frame_rate,  p_dst->i_frame_rate_base, 0 );
}