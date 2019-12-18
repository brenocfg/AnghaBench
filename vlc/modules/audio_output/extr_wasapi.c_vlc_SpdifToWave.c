#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int i_format; int i_rate; int i_bytes_per_frame; int i_frame_length; } ;
typedef  TYPE_3__ audio_sample_format_t ;
struct TYPE_8__ {int nChannels; int nSamplesPerSec; int wBitsPerSample; int nBlockAlign; int nAvgBytesPerSec; int cbSize; int /*<<< orphan*/  wFormatTag; } ;
struct TYPE_7__ {int wValidBitsPerSample; } ;
struct TYPE_10__ {int dwChannelMask; TYPE_2__ Format; TYPE_1__ Samples; int /*<<< orphan*/  SubFormat; } ;
typedef  TYPE_4__ WAVEFORMATEXTENSIBLE ;

/* Variables and functions */
 int SPEAKER_FRONT_LEFT ; 
 int SPEAKER_FRONT_RIGHT ; 
#define  VLC_CODEC_A52 131 
#define  VLC_CODEC_DTS 130 
#define  VLC_CODEC_SPDIFB 129 
#define  VLC_CODEC_SPDIFL 128 
 int /*<<< orphan*/  WAVE_FORMAT_EXTENSIBLE ; 
 int /*<<< orphan*/  _KSDATAFORMAT_SUBTYPE_IEC61937_DOLBY_DIGITAL ; 
 int /*<<< orphan*/  _KSDATAFORMAT_SUBTYPE_IEC61937_DTS ; 
 int /*<<< orphan*/  _KSDATAFORMAT_SUBTYPE_WAVEFORMATEX ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static void vlc_SpdifToWave(WAVEFORMATEXTENSIBLE *restrict wf,
                            audio_sample_format_t *restrict audio)
{
    switch (audio->i_format)
    {
    case VLC_CODEC_DTS:
        if (audio->i_rate < 48000)
        {
            /* Wasapi doesn't accept DTS @ 44.1kHz but accept IEC 60958 PCM */
            wf->SubFormat = _KSDATAFORMAT_SUBTYPE_WAVEFORMATEX;
        }
        else
            wf->SubFormat = _KSDATAFORMAT_SUBTYPE_IEC61937_DTS;
        break;
    case VLC_CODEC_SPDIFL:
    case VLC_CODEC_SPDIFB:
    case VLC_CODEC_A52:
        wf->SubFormat = _KSDATAFORMAT_SUBTYPE_IEC61937_DOLBY_DIGITAL;
        break;
    default:
        vlc_assert_unreachable();
    }

    wf->Format.wFormatTag = WAVE_FORMAT_EXTENSIBLE;
    wf->Format.nChannels = 2; /* To prevent channel re-ordering */
    wf->Format.nSamplesPerSec = audio->i_rate;
    wf->Format.wBitsPerSample = 16;
    wf->Format.nBlockAlign = 4; /* wf->Format.wBitsPerSample / 8 * wf->Format.nChannels  */
    wf->Format.nAvgBytesPerSec = wf->Format.nSamplesPerSec * wf->Format.nBlockAlign;
    wf->Format.cbSize = sizeof (*wf) - sizeof (wf->Format);

    wf->Samples.wValidBitsPerSample = wf->Format.wBitsPerSample;

    wf->dwChannelMask = SPEAKER_FRONT_LEFT | SPEAKER_FRONT_RIGHT;

    audio->i_format = VLC_CODEC_SPDIFL;
    audio->i_bytes_per_frame = wf->Format.nBlockAlign;
    audio->i_frame_length = 1;
}