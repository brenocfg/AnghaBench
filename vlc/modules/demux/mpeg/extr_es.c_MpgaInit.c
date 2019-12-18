#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_9__ {char* psz_version; int i_lowpass; } ;
typedef  TYPE_2__ lame_extra_t ;
struct TYPE_10__ {int /*<<< orphan*/  s; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ demux_t ;
struct TYPE_8__ {scalar_t__ i_frames; scalar_t__ i_bytes; int b_lame; TYPE_2__ lame; int /*<<< orphan*/  i_frame_samples; void* i_bitrate_avg; } ;
struct TYPE_11__ {int i_packet_size; float* rgf_replay_peak; float* rgf_replay_gain; TYPE_1__ xing; } ;
typedef  TYPE_4__ demux_sys_t ;

/* Variables and functions */
 size_t AUDIO_REPLAY_GAIN_ALBUM ; 
 size_t AUDIO_REPLAY_GAIN_TRACK ; 
 int GetDWBE (int const*) ; 
 int /*<<< orphan*/  ID3Parse (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ID3TAG_Parse_Handler ; 
 int MPGA_MODE (int const) ; 
 scalar_t__ MPGA_VERSION (int const) ; 
 int /*<<< orphan*/  MpgaCheckSync (int const*) ; 
 int /*<<< orphan*/  MpgaGetFrameSamples (int const) ; 
 void* MpgaXingGetDWBE (int const**,int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MpgaXingGetWBE (int const**,int*,int /*<<< orphan*/ ) ; 
 scalar_t__ MpgaXingLameConvertGain (int /*<<< orphan*/ ) ; 
 scalar_t__ MpgaXingLameConvertPeak (int) ; 
 int /*<<< orphan*/  MpgaXingSkip (int const**,int*,int) ; 
 int VLC_SUCCESS ; 
 scalar_t__ memcmp (int const*,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,int const*,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_3__*,char*,scalar_t__,...) ; 
 int vlc_stream_Peek (int /*<<< orphan*/ ,int const**,int) ; 

__attribute__((used)) static int MpgaInit( demux_t *p_demux )
{
    demux_sys_t *p_sys = p_demux->p_sys;

    const uint8_t *p_peek;
    int i_peek;

    /* */
    p_sys->i_packet_size = 1024;

    ID3Parse( p_demux, ID3TAG_Parse_Handler );

    /* Load a potential xing header */
    i_peek = vlc_stream_Peek( p_demux->s, &p_peek, 4 + 1024 );
    if( i_peek < 4 + 21 )
        return VLC_SUCCESS;

    const uint32_t header = GetDWBE( p_peek );
    if( !MpgaCheckSync( p_peek ) )
        return VLC_SUCCESS;

    /* Xing header */
    const uint8_t *p_xing = p_peek;
    int i_xing = i_peek;
    int i_skip;

    if( MPGA_VERSION( header ) == 0 )
        i_skip = MPGA_MODE( header ) != 3 ? 36 : 21;
    else
        i_skip = MPGA_MODE( header ) != 3 ? 21 : 13;

    if( i_skip + 8 >= i_xing || memcmp( &p_xing[i_skip], "Xing", 4 ) )
        return VLC_SUCCESS;

    const uint32_t i_flags = GetDWBE( &p_xing[i_skip+4] );

    MpgaXingSkip( &p_xing, &i_xing, i_skip + 8 );

    if( i_flags&0x01 )
        p_sys->xing.i_frames = MpgaXingGetDWBE( &p_xing, &i_xing, 0 );
    if( i_flags&0x02 )
        p_sys->xing.i_bytes = MpgaXingGetDWBE( &p_xing, &i_xing, 0 );
    if( i_flags&0x04 ) /* TODO Support XING TOC to improve seeking accuracy */
        MpgaXingSkip( &p_xing, &i_xing, 100 );
    if( i_flags&0x08 )
    {
        /* FIXME: doesn't return the right bitrage average, at least
           with some MP3's */
        p_sys->xing.i_bitrate_avg = MpgaXingGetDWBE( &p_xing, &i_xing, 0 );
        msg_Dbg( p_demux, "xing vbr value present (%d)",
                 p_sys->xing.i_bitrate_avg );
    }

    if( p_sys->xing.i_frames > 0 && p_sys->xing.i_bytes > 0 )
    {
        p_sys->xing.i_frame_samples = MpgaGetFrameSamples( header );
        msg_Dbg( p_demux, "xing frames&bytes value present "
                 "(%d bytes, %d frames, %d samples/frame)",
                 p_sys->xing.i_bytes, p_sys->xing.i_frames,
                 p_sys->xing.i_frame_samples );
    }

    if( i_xing >= 20 && memcmp( p_xing, "LAME", 4 ) == 0)
    {
        p_sys->xing.b_lame = true;
        lame_extra_t *p_lame = &p_sys->xing.lame;

        memcpy( p_lame->psz_version, p_xing, 9 );
        p_lame->psz_version[9] = '\0';

        MpgaXingSkip( &p_xing, &i_xing, 9 );
        MpgaXingSkip( &p_xing, &i_xing, 1 ); /* rev_method */

        p_lame->i_lowpass = (*p_xing) * 100;
        MpgaXingSkip( &p_xing, &i_xing, 1 );

        uint32_t peak  = MpgaXingGetDWBE( &p_xing, &i_xing, 0 );
        uint16_t track = MpgaXingGetWBE( &p_xing, &i_xing, 0 );
        uint16_t album = MpgaXingGetWBE( &p_xing, &i_xing, 0 );

        p_sys->rgf_replay_peak[AUDIO_REPLAY_GAIN_TRACK] = (float) MpgaXingLameConvertPeak( peak );
        p_sys->rgf_replay_gain[AUDIO_REPLAY_GAIN_TRACK] = (float) MpgaXingLameConvertGain( track );
        p_sys->rgf_replay_gain[AUDIO_REPLAY_GAIN_ALBUM] = (float) MpgaXingLameConvertGain( album );

        MpgaXingSkip( &p_xing, &i_xing, 1 ); /* flags */
    }

    return VLC_SUCCESS;
}