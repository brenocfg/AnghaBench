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
struct TYPE_10__ {int i_format; int i_rate; int i_bytes_per_frame; int i_physical_channels; int /*<<< orphan*/  i_bitspersample; int /*<<< orphan*/  i_channels; } ;
typedef  TYPE_3__ audio_sample_format_t ;
struct TYPE_9__ {int /*<<< orphan*/  wValidBitsPerSample; } ;
struct TYPE_8__ {int nSamplesPerSec; int nAvgBytesPerSec; int nBlockAlign; int cbSize; int /*<<< orphan*/  wBitsPerSample; int /*<<< orphan*/  nChannels; int /*<<< orphan*/  wFormatTag; } ;
struct TYPE_11__ {int /*<<< orphan*/  dwChannelMask; TYPE_2__ Samples; TYPE_1__ Format; void* SubFormat; } ;
typedef  TYPE_4__ WAVEFORMATEXTENSIBLE ;

/* Variables and functions */
 void* KSDATAFORMAT_SUBTYPE_IEEE_FLOAT ; 
 void* KSDATAFORMAT_SUBTYPE_PCM ; 
#define  VLC_CODEC_FL32 131 
#define  VLC_CODEC_FL64 130 
#define  VLC_CODEC_S16N 129 
#define  VLC_CODEC_U8 128 
 int /*<<< orphan*/  WAVE_FORMAT_EXTENSIBLE ; 
 int /*<<< orphan*/  aout_FormatPrepare (TYPE_3__*) ; 
 int /*<<< orphan*/ * chans_in ; 
 int* pi_vlc_chan_order_wg4 ; 

__attribute__((used)) static void vlc_ToWave(WAVEFORMATEXTENSIBLE *restrict wf,
                       audio_sample_format_t *restrict audio)
{
    switch (audio->i_format)
    {
        case VLC_CODEC_FL64:
            audio->i_format = VLC_CODEC_FL32;
            /* fall through */
        case VLC_CODEC_FL32:
            wf->SubFormat = KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;
            break;

        case VLC_CODEC_U8:
            audio->i_format = VLC_CODEC_S16N;
            /* fall through */
        case VLC_CODEC_S16N:
            wf->SubFormat = KSDATAFORMAT_SUBTYPE_PCM;
            break;

        default:
            audio->i_format = VLC_CODEC_FL32;
            wf->SubFormat = KSDATAFORMAT_SUBTYPE_IEEE_FLOAT;
            break;
    }
    aout_FormatPrepare (audio);

    wf->Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
    wf->Format.nChannels = audio->i_channels;
    wf->Format.nSamplesPerSec = audio->i_rate;
    wf->Format.nAvgBytesPerSec = audio->i_bytes_per_frame * audio->i_rate;
    wf->Format.nBlockAlign = audio->i_bytes_per_frame;
    wf->Format.wBitsPerSample = audio->i_bitspersample;
    wf->Format.cbSize = sizeof (*wf) - sizeof (wf->Format);

    wf->Samples.wValidBitsPerSample = audio->i_bitspersample;

    wf->dwChannelMask = 0;
    for (unsigned i = 0; pi_vlc_chan_order_wg4[i]; i++)
        if (audio->i_physical_channels & pi_vlc_chan_order_wg4[i])
            wf->dwChannelMask |= chans_in[i];
}