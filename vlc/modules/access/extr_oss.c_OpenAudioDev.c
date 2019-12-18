#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int i_channels; int i_rate; int i_bitspersample; int i_blockalign; } ;
struct TYPE_11__ {int i_bitrate; TYPE_1__ audio; } ;
typedef  TYPE_2__ es_format_t ;
struct TYPE_12__ {int /*<<< orphan*/  out; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_13__ {int i_sample_rate; int /*<<< orphan*/  p_es; scalar_t__ b_stereo; int /*<<< orphan*/  psz_device; } ;
typedef  TYPE_4__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  AUDIO_ES ; 
 int OpenAudioDevOss (TYPE_3__*) ; 
 int /*<<< orphan*/  VLC_CODEC_S16L ; 
 int /*<<< orphan*/  es_format_Init (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  es_out_Add (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,int,...) ; 

__attribute__((used)) static int OpenAudioDev( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;
    int i_fd = OpenAudioDevOss( p_demux );

    if( i_fd < 0 )
        return i_fd;

    msg_Dbg( p_demux, "opened adev=`%s' %s %dHz",
             p_sys->psz_device, p_sys->b_stereo ? "stereo" : "mono",
             p_sys->i_sample_rate );

    es_format_t fmt;
    es_format_Init( &fmt, AUDIO_ES, VLC_CODEC_S16L );

    fmt.audio.i_channels = p_sys->b_stereo ? 2 : 1;
    fmt.audio.i_rate = p_sys->i_sample_rate;
    fmt.audio.i_bitspersample = 16;
    fmt.audio.i_blockalign = fmt.audio.i_channels * fmt.audio.i_bitspersample / 8;
    fmt.i_bitrate = fmt.audio.i_channels * fmt.audio.i_rate * fmt.audio.i_bitspersample;

    msg_Dbg( p_demux, "new audio es %d channels %dHz",
             fmt.audio.i_channels, fmt.audio.i_rate );

    p_sys->p_es = es_out_Add( p_demux->out, &fmt );

    return i_fd;
}