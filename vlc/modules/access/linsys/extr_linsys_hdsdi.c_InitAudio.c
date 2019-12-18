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
struct TYPE_11__ {int i_channel; int /*<<< orphan*/  p_es; int /*<<< orphan*/  i_id; int /*<<< orphan*/  i_delay; } ;
typedef  TYPE_2__ hdsdi_audio_t ;
struct TYPE_10__ {int i_channels; int i_rate; int i_bitspersample; int i_blockalign; int /*<<< orphan*/  i_physical_channels; } ;
struct TYPE_12__ {int i_bitrate; TYPE_1__ audio; int /*<<< orphan*/  i_id; } ;
typedef  TYPE_3__ es_format_t ;
struct TYPE_13__ {int /*<<< orphan*/  out; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ demux_t ;
struct TYPE_14__ {int i_sample_rate; int i_ablock_size; int i_frame_rate_base; int i_frame_rate; int /*<<< orphan*/  i_aincr; int /*<<< orphan*/  i_next_adate; TYPE_2__* p_audios; } ;
typedef  TYPE_5__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOUT_CHANS_STEREO ; 
 int /*<<< orphan*/  AUDIO_ES ; 
 int MAX_AUDIOS ; 
 int /*<<< orphan*/  START_DATE ; 
 int /*<<< orphan*/  VLC_CODEC_S16L ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  es_format_Init (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_out_Add (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*,int,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_tick_from_samples (int,int) ; 

__attribute__((used)) static int InitAudio( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    es_format_t fmt;

    for ( int i = 0; i < MAX_AUDIOS; i++ )
    {
        hdsdi_audio_t *p_audio = &p_sys->p_audios[i];

        if ( p_audio->i_channel == -1 ) continue;

        msg_Dbg( p_demux, "starting audio %u/%u rate:%u delay:%d",
                 1 + p_audio->i_channel / 2, 1 + (p_audio->i_channel % 2),
                 p_sys->i_sample_rate, p_audio->i_delay );

        es_format_Init( &fmt, AUDIO_ES, VLC_CODEC_S16L );
        fmt.i_id = p_audio->i_id;
        fmt.audio.i_channels          = 2;
        fmt.audio.i_physical_channels = AOUT_CHANS_STEREO;
        fmt.audio.i_rate              = p_sys->i_sample_rate;
        fmt.audio.i_bitspersample     = 16;
        fmt.audio.i_blockalign = fmt.audio.i_channels *
            fmt.audio.i_bitspersample / 8;
        fmt.i_bitrate = fmt.audio.i_channels * fmt.audio.i_rate *
            fmt.audio.i_bitspersample;
        p_audio->p_es = es_out_Add( p_demux->out, &fmt );
    }

    p_sys->i_next_adate = START_DATE;
    p_sys->i_ablock_size = p_sys->i_sample_rate * 4 * p_sys->i_frame_rate_base / p_sys->i_frame_rate;
    p_sys->i_aincr = vlc_tick_from_samples(p_sys->i_ablock_size, p_sys->i_sample_rate * 4);

    return VLC_SUCCESS;
}