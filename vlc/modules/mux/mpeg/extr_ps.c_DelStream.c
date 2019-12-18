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
struct TYPE_12__ {int i_rate_bound; int /*<<< orphan*/  i_psm_version; int /*<<< orphan*/  i_instant_bitrate; int /*<<< orphan*/  i_video_bound; int /*<<< orphan*/  i_audio_bound; int /*<<< orphan*/  stream_id_spu; int /*<<< orphan*/  stream_id_mpga; int /*<<< orphan*/  stream_id_a52; int /*<<< orphan*/  stream_id_dts; int /*<<< orphan*/  stream_id_lpcm; int /*<<< orphan*/  stream_id_mpgv; } ;
typedef  TYPE_3__ sout_mux_sys_t ;
struct TYPE_13__ {TYPE_1__* p_fmt; scalar_t__ p_sys; } ;
typedef  TYPE_4__ sout_input_t ;
struct TYPE_14__ {int i_stream_id; } ;
typedef  TYPE_5__ ps_stream_t ;
struct TYPE_10__ {int i_codec; scalar_t__ i_cat; int i_bitrate; } ;

/* Variables and functions */
 scalar_t__ AUDIO_ES ; 
 int /*<<< orphan*/  StreamIdRelease (int /*<<< orphan*/ ,int,int) ; 
 scalar_t__ VIDEO_ES ; 
#define  VLC_CODEC_A52 133 
#define  VLC_CODEC_DTS 132 
#define  VLC_CODEC_DVD_LPCM 131 
#define  VLC_CODEC_MPGA 130 
#define  VLC_CODEC_MPGV 129 
#define  VLC_CODEC_SPU 128 
 int /*<<< orphan*/  free (TYPE_5__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_2__*,char*) ; 

__attribute__((used)) static void DelStream( sout_mux_t *p_mux, sout_input_t *p_input )
{
    sout_mux_sys_t *p_sys = p_mux->p_sys;
    ps_stream_t *p_stream =(ps_stream_t*)p_input->p_sys;

    msg_Dbg( p_mux, "removing input" );
    switch( p_input->p_fmt->i_codec )
    {
        case VLC_CODEC_MPGV:
            StreamIdRelease( p_sys->stream_id_mpgv, 0xe0,
                             p_stream->i_stream_id );
            break;
        case VLC_CODEC_DVD_LPCM:
            StreamIdRelease( p_sys->stream_id_lpcm, 0xa0,
                             p_stream->i_stream_id&0xff );
            break;
        case VLC_CODEC_DTS:
            StreamIdRelease( p_sys->stream_id_dts, 0x88,
                             p_stream->i_stream_id&0xff );
            break;
        case VLC_CODEC_A52:
            StreamIdRelease( p_sys->stream_id_a52, 0x80,
                             p_stream->i_stream_id&0xff );
            break;
        case VLC_CODEC_MPGA:
            StreamIdRelease( p_sys->stream_id_mpga, 0xc0,
                             p_stream->i_stream_id  );
            break;
        case VLC_CODEC_SPU:
            StreamIdRelease( p_sys->stream_id_spu, 0x20,
                             p_stream->i_stream_id&0xff );
            break;
        default:
            /* Never reached */
            break;
    }

    if( p_input->p_fmt->i_cat == AUDIO_ES )
    {
        p_sys->i_audio_bound--;
    }
    else if( p_input->p_fmt->i_cat == VIDEO_ES )
    {
        p_sys->i_video_bound--;
    }

    /* Try to set a sensible default value for the instant bitrate */
    p_sys->i_instant_bitrate -= (p_input->p_fmt->i_bitrate + 1000);
    /* rate_bound is in units of 50 bytes/second */
    p_sys->i_rate_bound -= (p_input->p_fmt->i_bitrate * 2)/(8 * 50);

    p_sys->i_psm_version++;

    free( p_stream );
}