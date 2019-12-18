#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int vlc_tick_t ;
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint64_t ;
struct TYPE_18__ {TYPE_7__* p_sys; } ;
typedef  TYPE_6__ sout_mux_t ;
struct TYPE_16__ {int i_index_intvl; double i_index_ratio; } ;
struct TYPE_19__ {TYPE_4__ skeleton; } ;
typedef  TYPE_7__ sout_mux_sys_t ;
struct TYPE_20__ {TYPE_3__* p_fmt; scalar_t__ p_sys; } ;
typedef  TYPE_8__ sout_input_t ;
struct TYPE_17__ {size_t i_index_size; scalar_t__ i_index_payload; int /*<<< orphan*/  p_index; } ;
struct TYPE_13__ {int i_frame_rate; int i_frame_rate_base; } ;
struct TYPE_14__ {TYPE_1__ video; } ;
struct TYPE_21__ {int i_length; TYPE_5__ skeleton; TYPE_2__ fmt; } ;
typedef  TYPE_9__ ogg_stream_t ;
struct TYPE_15__ {scalar_t__ i_cat; int /*<<< orphan*/  i_bitrate; } ;

/* Variables and functions */
 double CLOCK_FREQ ; 
 double INT64_C (int) ; 
 scalar_t__ VIDEO_ES ; 
 int VLC_TICK_FROM_SEC (int) ; 
 int __MAX (int,int) ; 
 int /*<<< orphan*/  calloc (size_t,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_6__*,char*,...) ; 
 int samples_from_vlc_tick (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool AllocateIndex( sout_mux_t *p_mux, sout_input_t *p_input )
{
    sout_mux_sys_t *p_sys = p_mux->p_sys;
    ogg_stream_t *p_stream = (ogg_stream_t *) p_input->p_sys;
    size_t i_size;

    if ( p_stream->i_length )
    {
        vlc_tick_t i_interval = p_sys->skeleton.i_index_intvl;
        uint64_t i;

        if( p_input->p_fmt->i_cat == VIDEO_ES &&
                p_stream->fmt.video.i_frame_rate )
        {
            /* optimize for fps < 1 */
            i_interval= __MAX( i_interval,
                       VLC_TICK_FROM_SEC(10) *
                       p_stream->fmt.video.i_frame_rate_base /
                       p_stream->fmt.video.i_frame_rate );
        }

        size_t i_tuple_size = 0;
        /* estimate length of pos value */
        if ( p_input->p_fmt->i_bitrate )
        {
            i = samples_from_vlc_tick(i_interval, p_input->p_fmt->i_bitrate);
            while ( i <<= 1 ) i_tuple_size++;
        }
        else
        {
            /* Likely 64KB<<keyframe interval<<16MB */
            /* We can't really guess due to muxing */
            i_tuple_size = 24 / 8;
        }

        /* add length of interval value */
        i = i_interval;
        while ( i <<= 1 ) i_tuple_size++;

        i_size = i_tuple_size * ( p_stream->i_length / i_interval + 2 );
    }
    else
    {
        i_size = ( INT64_C(3600) * 11.2 * CLOCK_FREQ / p_sys->skeleton.i_index_intvl )
                * p_sys->skeleton.i_index_ratio;
        msg_Dbg( p_mux, "No stream length, using default allocation for index" );
    }
    i_size *= ( 8.0 / 7 ); /* 7bits encoding overhead */
    msg_Dbg( p_mux, "allocating %zu bytes for index", i_size );
    p_stream->skeleton.p_index = calloc( i_size, sizeof(uint8_t) );
    if ( !p_stream->skeleton.p_index ) return false;
    p_stream->skeleton.i_index_size = i_size;
    p_stream->skeleton.i_index_payload = 0;
    return true;
}