#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ sout_mux_t ;
struct TYPE_12__ {int i_bitrate; int b_write_header; int /*<<< orphan*/  tracks; scalar_t__ b_asf_http; int /*<<< orphan*/  i_bitrate_override; } ;
typedef  TYPE_3__ sout_mux_sys_t ;
struct TYPE_13__ {TYPE_1__* p_fmt; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ sout_input_t ;
struct TYPE_14__ {scalar_t__ i_cat; } ;
typedef  TYPE_5__ asf_track_t ;
struct TYPE_10__ {int i_bitrate; } ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 scalar_t__ VIDEO_ES ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  vlc_array_index_of_item (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  vlc_array_remove (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void DelStream( sout_mux_t *p_mux, sout_input_t *p_input )
{
    /* if bitrate ain't defined in commandline, reduce it when tracks are deleted
     */
    sout_mux_sys_t   *p_sys = p_mux->p_sys;
    asf_track_t      *tk = p_input->p_sys;
    msg_Dbg( p_mux, "removing input" );
    if(!p_sys->i_bitrate_override)
    {
        if( tk->i_cat == AUDIO_ES )
        {
             if( p_input->p_fmt->i_bitrate > 24000 )
                 p_sys->i_bitrate -= p_input->p_fmt->i_bitrate;
             else
                 p_sys->i_bitrate -= 128000;
        }
        else if(tk->i_cat == VIDEO_ES )
        {
             if( p_input->p_fmt->i_bitrate > 50000 )
                 p_sys->i_bitrate -= p_input->p_fmt->i_bitrate;
             else
                 p_sys->i_bitrate -= 512000;
        }
    }

    if( p_sys->b_asf_http )
    {
        vlc_array_remove( &p_sys->tracks, vlc_array_index_of_item( &p_sys->tracks, tk ) );
        p_sys->b_write_header = true;
    }
}