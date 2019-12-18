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
struct TYPE_9__ {scalar_t__ i_channels; int /*<<< orphan*/  i_physical_channels; int /*<<< orphan*/  i_format; int /*<<< orphan*/  i_rate; } ;
typedef  TYPE_2__ audio_sample_format_t ;
struct TYPE_8__ {int wValidBitsPerSample; } ;
struct TYPE_10__ {int dwChannelMask; TYPE_1__ Samples; int /*<<< orphan*/  SubFormat; } ;
typedef  TYPE_3__ WAVEFORMATEXTENSIBLE ;
struct TYPE_11__ {scalar_t__ wFormatTag; int wBitsPerSample; scalar_t__ nChannels; int /*<<< orphan*/  nSamplesPerSec; } ;
typedef  TYPE_4__ WAVEFORMATEX ;

/* Variables and functions */
 scalar_t__ IsEqualIID (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KSDATAFORMAT_SUBTYPE_IEEE_FLOAT ; 
 int /*<<< orphan*/  KSDATAFORMAT_SUBTYPE_PCM ; 
 int /*<<< orphan*/  VLC_CODEC_FL32 ; 
 int /*<<< orphan*/  VLC_CODEC_FL64 ; 
 int /*<<< orphan*/  VLC_CODEC_S16N ; 
 int /*<<< orphan*/  VLC_CODEC_S32N ; 
 scalar_t__ WAVE_FORMAT_EXTENSIBLE ; 
 int /*<<< orphan*/  aout_FormatPrepare (TYPE_2__*) ; 
 int* chans_in ; 
 int /*<<< orphan*/ * pi_vlc_chan_order_wg4 ; 

__attribute__((used)) static int vlc_FromWave(const WAVEFORMATEX *restrict wf,
                        audio_sample_format_t *restrict audio)
{
    audio->i_rate = wf->nSamplesPerSec;
    audio->i_physical_channels = 0;

    if (wf->wFormatTag == WAVE_FORMAT_EXTENSIBLE)
    {
        const WAVEFORMATEXTENSIBLE *wfe = (void *)wf;

        if (IsEqualIID(&wfe->SubFormat, &KSDATAFORMAT_SUBTYPE_IEEE_FLOAT))
        {
            switch (wf->wBitsPerSample)
            {
                case 64:
                    audio->i_format = VLC_CODEC_FL64;
                    break;
                case 32:
                    audio->i_format = VLC_CODEC_FL32;
                    break;
                default:
                    return -1;
            }
        }
        else if (IsEqualIID(&wfe->SubFormat, &KSDATAFORMAT_SUBTYPE_PCM))
        {
            switch (wf->wBitsPerSample)
            {
                case 32:
                    audio->i_format = VLC_CODEC_S32N;
                    break;
                case 16:
                    audio->i_format = VLC_CODEC_S16N;
                    break;
                default:
                    return -1;
            }
        }

        if (wfe->Samples.wValidBitsPerSample != wf->wBitsPerSample)
            return -1;

        for (unsigned i = 0; chans_in[i]; i++)
            if (wfe->dwChannelMask & chans_in[i])
                audio->i_physical_channels |= pi_vlc_chan_order_wg4[i];
    }
    else
        return -1;

    aout_FormatPrepare (audio);

    if (wf->nChannels != audio->i_channels)
        return -1;
    return 0;
}