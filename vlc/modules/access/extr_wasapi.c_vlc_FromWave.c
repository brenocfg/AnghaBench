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
struct TYPE_9__ {scalar_t__ i_channels; int /*<<< orphan*/  i_format; int /*<<< orphan*/  i_physical_channels; int /*<<< orphan*/  i_rate; } ;
typedef  TYPE_2__ audio_sample_format_t ;
struct TYPE_8__ {int wValidBitsPerSample; } ;
struct TYPE_10__ {int dwChannelMask; int /*<<< orphan*/  SubFormat; TYPE_1__ Samples; } ;
typedef  TYPE_3__ WAVEFORMATEXTENSIBLE ;
struct TYPE_11__ {scalar_t__ wFormatTag; scalar_t__ nChannels; scalar_t__ wBitsPerSample; int /*<<< orphan*/  nSamplesPerSec; } ;
typedef  TYPE_4__ WAVEFORMATEX ;

/* Variables and functions */
 int /*<<< orphan*/  AOUT_CHAN_CENTER ; 
 int /*<<< orphan*/  AOUT_CHAN_LEFT ; 
 int /*<<< orphan*/  AOUT_CHAN_LFE ; 
 int /*<<< orphan*/  AOUT_CHAN_RIGHT ; 
 scalar_t__ IsEqualIID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KSDATAFORMAT_SUBTYPE_ADPCM ; 
 int /*<<< orphan*/  KSDATAFORMAT_SUBTYPE_ALAW ; 
 int /*<<< orphan*/  KSDATAFORMAT_SUBTYPE_IEEE_FLOAT ; 
 int /*<<< orphan*/  KSDATAFORMAT_SUBTYPE_MULAW ; 
 int /*<<< orphan*/  KSDATAFORMAT_SUBTYPE_PCM ; 
 int SPEAKER_FRONT_CENTER ; 
 int SPEAKER_FRONT_LEFT ; 
 int SPEAKER_FRONT_RIGHT ; 
 int SPEAKER_LOW_FREQUENCY ; 
 int /*<<< orphan*/  VLC_CODEC_ADPCM_MS ; 
 int /*<<< orphan*/  VLC_CODEC_ALAW ; 
 int /*<<< orphan*/  VLC_CODEC_FL32 ; 
 int /*<<< orphan*/  VLC_CODEC_FL64 ; 
 int /*<<< orphan*/  VLC_CODEC_MULAW ; 
 int /*<<< orphan*/  VLC_CODEC_S16N ; 
 int /*<<< orphan*/  VLC_CODEC_S24B32 ; 
 int /*<<< orphan*/  VLC_CODEC_S24L32 ; 
 int /*<<< orphan*/  VLC_CODEC_S24N ; 
 int /*<<< orphan*/  VLC_CODEC_S32N ; 
 int /*<<< orphan*/  VLC_CODEC_S8 ; 
 scalar_t__ WAVE_FORMAT_EXTENSIBLE ; 
 int /*<<< orphan*/  aout_FormatPrepare (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ vlc_popcount (int) ; 

__attribute__((used)) static int vlc_FromWave(const WAVEFORMATEX *restrict wf,
                        audio_sample_format_t *restrict fmt)
{
    fmt->i_rate = wf->nSamplesPerSec;

    /* As per MSDN, IAudioClient::GetMixFormat() always uses this format. */
    assert(wf->wFormatTag == WAVE_FORMAT_EXTENSIBLE);

    const WAVEFORMATEXTENSIBLE *wfe = (void *)wf;

    fmt->i_physical_channels = 0;
    if (wfe->dwChannelMask & SPEAKER_FRONT_LEFT)
        fmt->i_physical_channels |= AOUT_CHAN_LEFT;
    if (wfe->dwChannelMask & SPEAKER_FRONT_RIGHT)
        fmt->i_physical_channels |= AOUT_CHAN_RIGHT;
    if (wfe->dwChannelMask & SPEAKER_FRONT_CENTER)
        fmt->i_physical_channels |= AOUT_CHAN_CENTER;
    if (wfe->dwChannelMask & SPEAKER_LOW_FREQUENCY)
        fmt->i_physical_channels |= AOUT_CHAN_LFE;

    assert(vlc_popcount(wfe->dwChannelMask) == wf->nChannels);

    if (IsEqualIID(&wfe->SubFormat, &KSDATAFORMAT_SUBTYPE_PCM))
    {
        switch (wf->wBitsPerSample)
        {
            case 32:
                switch (wfe->Samples.wValidBitsPerSample)
                {
                    case 32:
                        fmt->i_format = VLC_CODEC_S32N;
                        break;
                    case 24:
#ifdef WORDS_BIGENDIAN
                        fmt->i_format = VLC_CODEC_S24B32;
#else
                        fmt->i_format = VLC_CODEC_S24L32;
#endif
                        break;
                    default:
                        return -1;
                }
                break;
            case 24:
                if (wfe->Samples.wValidBitsPerSample == 24)
                    fmt->i_format = VLC_CODEC_S24N;
                else
                    return -1;
                break;
            case 16:
                if (wfe->Samples.wValidBitsPerSample == 16)
                    fmt->i_format = VLC_CODEC_S16N;
                else
                    return -1;
                break;
            case 8:
                if (wfe->Samples.wValidBitsPerSample == 8)
                    fmt->i_format = VLC_CODEC_S8;
                else
                    return -1;
                break;
            default:
                return -1;
        }
    }
    else if (IsEqualIID(&wfe->SubFormat, &KSDATAFORMAT_SUBTYPE_IEEE_FLOAT))
    {
        if (wf->wBitsPerSample != wfe->Samples.wValidBitsPerSample)
            return -1;

        switch (wf->wBitsPerSample)
        {
            case 64:
                fmt->i_format = VLC_CODEC_FL64;
                break;
            case 32:
                fmt->i_format = VLC_CODEC_FL32;
                break;
            default:
                return -1;
        }
    }
    /*else if (IsEqualIID(&wfe->Subformat, &KSDATAFORMAT_SUBTYPE_DRM)) {} */
    else if (IsEqualIID(&wfe->SubFormat, &KSDATAFORMAT_SUBTYPE_ALAW))
        fmt->i_format = VLC_CODEC_ALAW;
    else if (IsEqualIID(&wfe->SubFormat, &KSDATAFORMAT_SUBTYPE_MULAW))
        fmt->i_format = VLC_CODEC_MULAW;
    else if (IsEqualIID(&wfe->SubFormat, &KSDATAFORMAT_SUBTYPE_ADPCM))
        fmt->i_format = VLC_CODEC_ADPCM_MS;
    else
        return -1;

    aout_FormatPrepare(fmt);
    if (wf->nChannels != fmt->i_channels)
        return -1;

    return 0;
}