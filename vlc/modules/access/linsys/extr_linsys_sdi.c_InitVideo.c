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
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_6__ {int i_anc_size; int i_active_size; int i_width; int i_nb_lines; int i_frame_rate; int i_frame_rate_base; int i_height; int i_aspect; int b_hd; int b_vbi; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int VOUT_ASPECT_FACTOR ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*) ; 

__attribute__((used)) static void InitVideo( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    int i_total_width = (p_sys->i_anc_size + p_sys->i_active_size) * 4 / 5;
    p_sys->i_width = (p_sys->i_active_size - 5) * 4 / 10;
    if ( p_sys->i_nb_lines == 625 )
    {
        /* PAL */
        p_sys->i_frame_rate      = 25;
        p_sys->i_frame_rate_base = 1;
        p_sys->i_height          = 576;
        p_sys->i_aspect          = 4 * VOUT_ASPECT_FACTOR / 3;
        p_sys->b_hd              = false;
    }
    else if ( p_sys->i_nb_lines == 525 )
    {
        /* NTSC */
        p_sys->i_frame_rate      = 30000;
        p_sys->i_frame_rate_base = 1001;
        p_sys->i_height          = 480;
        p_sys->i_aspect          = 4 * VOUT_ASPECT_FACTOR / 3;
        p_sys->b_hd              = false;
    }
    else if ( p_sys->i_nb_lines == 1125 && i_total_width == 2640 )
    {
        /* 1080i50 or 1080p25 */
        p_sys->i_frame_rate      = 25;
        p_sys->i_frame_rate_base = 1;
        p_sys->i_height          = 1080;
        p_sys->i_aspect          = 16 * VOUT_ASPECT_FACTOR / 9;
        p_sys->b_hd              = true;
    }
    else if ( p_sys->i_nb_lines == 1125 && i_total_width == 2200 )
    {
        /* 1080i60 or 1080p30 */
        p_sys->i_frame_rate      = 30000;
        p_sys->i_frame_rate_base = 1001;
        p_sys->i_height          = 1080;
        p_sys->i_aspect          = 16 * VOUT_ASPECT_FACTOR / 9;
        p_sys->b_hd              = true;
    }
    else if ( p_sys->i_nb_lines == 750 && i_total_width == 1980 )
    {
        /* 720p50 */
        p_sys->i_frame_rate      = 50;
        p_sys->i_frame_rate_base = 1;
        p_sys->i_height          = 720;
        p_sys->i_aspect          = 16 * VOUT_ASPECT_FACTOR / 9;
        p_sys->b_hd              = true;
    }
    else if ( p_sys->i_nb_lines == 750 && i_total_width == 1650 )
    {
        /* 720p60 */
        p_sys->i_frame_rate      = 60000;
        p_sys->i_frame_rate_base = 1001;
        p_sys->i_height          = 720;
        p_sys->i_aspect          = 16 * VOUT_ASPECT_FACTOR / 9;
        p_sys->b_hd              = true;
    }
    else
    {
        msg_Warn( p_demux, "unable to determine video type" );
        /* Put sensitive defaults */
        p_sys->i_frame_rate      = 25;
        p_sys->i_frame_rate_base = 1;
        p_sys->i_height          = p_sys->i_nb_lines;
        p_sys->i_aspect          = 16 * VOUT_ASPECT_FACTOR / 9;
        p_sys->b_hd              = true;
    }
    p_sys->b_vbi = !p_sys->b_hd;
}