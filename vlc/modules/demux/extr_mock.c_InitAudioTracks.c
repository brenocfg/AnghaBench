#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint16_t ;
struct demux_sys {scalar_t__ audio_rate; int audio_channels; int /*<<< orphan*/  audio_packetized; int /*<<< orphan*/  audio_format; } ;
struct TYPE_11__ {scalar_t__ i_rate; int /*<<< orphan*/  i_physical_channels; int /*<<< orphan*/  i_format; } ;
struct TYPE_9__ {TYPE_5__ audio; int /*<<< orphan*/  i_codec; } ;
typedef  TYPE_1__ es_format_t ;
struct TYPE_10__ {struct demux_sys* p_sys; } ;
typedef  TYPE_2__ demux_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOUT_CHANS_2_0 ; 
 int /*<<< orphan*/  AOUT_CHANS_2_1 ; 
 int /*<<< orphan*/  AOUT_CHANS_4_0 ; 
 int /*<<< orphan*/  AOUT_CHANS_4_1 ; 
 int /*<<< orphan*/  AOUT_CHANS_6_0 ; 
 int /*<<< orphan*/  AOUT_CHANS_7_0 ; 
 int /*<<< orphan*/  AOUT_CHANS_7_1 ; 
 int /*<<< orphan*/  AOUT_CHANS_8_1 ; 
 int /*<<< orphan*/  AOUT_CHAN_CENTER ; 
 int AOUT_CHAN_MAX ; 
 int /*<<< orphan*/  AUDIO_ES ; 
 scalar_t__ AppendMockTrack (TYPE_2__*,TYPE_1__*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ UINT_MAX ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 scalar_t__ aout_BitsPerSample (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aout_FormatPrepare (TYPE_5__*) ; 
 int /*<<< orphan*/  es_format_Init (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static int
InitAudioTracks(demux_t *demux, int group, size_t count)
{
    struct demux_sys *sys = demux->p_sys;

    if (count == 0)
        return VLC_SUCCESS;

    const bool rate_ok = sys->audio_rate > 0 && sys->audio_rate != UINT_MAX;
    const bool format_ok = aout_BitsPerSample(sys->audio_format) != 0;
    const bool channels_ok = sys->audio_channels > 0 &&
                             sys->audio_channels <= AOUT_CHAN_MAX;

    if (!rate_ok || !format_ok || !channels_ok)
    {
        if (!rate_ok)
            msg_Err(demux, "Invalid audio rate");
        if (!format_ok)
            msg_Err(demux, "Invalid audio format");
        if (!channels_ok)
            msg_Err(demux, "Invalid audio channels");
        return VLC_EGENERIC;
    }

    uint16_t physical_channels = 0;
    switch (sys->audio_channels)
    {
        case 1: physical_channels = AOUT_CHAN_CENTER; break;
        case 2: physical_channels = AOUT_CHANS_2_0; break;
        case 3: physical_channels = AOUT_CHANS_2_1; break;
        case 4: physical_channels = AOUT_CHANS_4_0; break;
        case 5: physical_channels = AOUT_CHANS_4_1; break;
        case 6: physical_channels = AOUT_CHANS_6_0; break;
        case 7: physical_channels = AOUT_CHANS_7_0; break;
        case 8: physical_channels = AOUT_CHANS_7_1; break;
        case 9: physical_channels = AOUT_CHANS_8_1; break;
        default: vlc_assert_unreachable();
    }

    for (size_t i = 0; i < count; ++i)
    {
        es_format_t fmt;
        es_format_Init(&fmt, AUDIO_ES, sys->audio_format);
        fmt.audio.i_format = fmt.i_codec;
        fmt.audio.i_rate = sys->audio_rate;
        fmt.audio.i_physical_channels = physical_channels;
        aout_FormatPrepare(&fmt.audio);

        if (AppendMockTrack(demux, &fmt, group, sys->audio_packetized))
            return VLC_ENOMEM;
    }

    return VLC_SUCCESS;
}