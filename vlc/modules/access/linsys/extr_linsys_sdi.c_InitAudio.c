#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int i_rate; int i_nb_samples; float i_max_samples; int /*<<< orphan*/  p_buffer; scalar_t__ i_block_number; scalar_t__ i_right_samples; scalar_t__ i_left_samples; int /*<<< orphan*/  p_es; int /*<<< orphan*/  i_id; int /*<<< orphan*/  i_delay; int /*<<< orphan*/  i_pair; int /*<<< orphan*/  i_group; } ;
typedef  TYPE_2__ sdi_audio_t ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_11__ {int i_channels; int i_rate; int i_bitspersample; int i_blockalign; int /*<<< orphan*/  i_physical_channels; } ;
struct TYPE_13__ {int i_bitrate; TYPE_1__ audio; int /*<<< orphan*/  i_id; } ;
typedef  TYPE_3__ es_format_t ;
struct TYPE_14__ {int /*<<< orphan*/  out; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ demux_t ;
struct TYPE_15__ {int i_frame_rate_base; int i_frame_rate; } ;
typedef  TYPE_5__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOUT_CHANS_STEREO ; 
 int /*<<< orphan*/  AUDIO_ES ; 
 float SAMPLERATE_TOLERANCE ; 
 int /*<<< orphan*/  VLC_CODEC_S16L ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  es_format_Init (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_out_Add (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_alloc (float,int) ; 

__attribute__((used)) static int InitAudio( demux_t *p_demux, sdi_audio_t *p_audio )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    es_format_t fmt;

    msg_Dbg( p_demux, "starting audio %u/%u rate:%u delay:%d", p_audio->i_group,
             p_audio->i_pair, p_audio->i_rate, p_audio->i_delay );

    es_format_Init( &fmt, AUDIO_ES, VLC_CODEC_S16L );
    fmt.i_id = p_audio->i_id;
    fmt.audio.i_channels          = 2;
    fmt.audio.i_physical_channels = AOUT_CHANS_STEREO;
    fmt.audio.i_rate              = p_audio->i_rate;
    fmt.audio.i_bitspersample     = 16;
    fmt.audio.i_blockalign        = fmt.audio.i_channels *
                                    fmt.audio.i_bitspersample / 8;
    fmt.i_bitrate                 = fmt.audio.i_channels * fmt.audio.i_rate *
                                    fmt.audio.i_bitspersample;
    p_audio->p_es                 = es_out_Add( p_demux->out, &fmt );

    p_audio->i_nb_samples         = p_audio->i_rate * p_sys->i_frame_rate_base
                                    / p_sys->i_frame_rate;
    p_audio->i_max_samples        = (float)p_audio->i_nb_samples *
                                    (1.f + SAMPLERATE_TOLERANCE);

    p_audio->p_buffer             = vlc_alloc( p_audio->i_max_samples, sizeof(int16_t) * 2 );
    p_audio->i_left_samples       = p_audio->i_right_samples = 0;
    p_audio->i_block_number       = 0;

    if( unlikely( !p_audio->p_buffer ) )
        return VLC_ENOMEM;
    return VLC_SUCCESS;
}