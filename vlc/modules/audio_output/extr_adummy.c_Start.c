#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int i_format; int i_bytes_per_frame; int i_frame_length; int i_rate; int /*<<< orphan*/  channel_type; } ;
typedef  TYPE_1__ audio_sample_format_t ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int AOUT_FMT_LINEAR (TYPE_1__*) ; 
 int /*<<< orphan*/  AUDIO_CHANNEL_TYPE_BITMAP ; 
 int /*<<< orphan*/  HAVE_FPU ; 
#define  VLC_CODEC_A52 132 
#define  VLC_CODEC_DTS 131 
#define  VLC_CODEC_EAC3 130 
 int VLC_CODEC_FL32 ; 
#define  VLC_CODEC_MLP 129 
 int VLC_CODEC_S16N ; 
 void* VLC_CODEC_SPDIFL ; 
#define  VLC_CODEC_TRUEHD 128 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  aout_FormatNbChannels (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int Start(audio_output_t *aout, audio_sample_format_t *restrict fmt)
{
    (void) aout;

    switch (fmt->i_format)
    {
        case VLC_CODEC_A52:
        case VLC_CODEC_EAC3:
            fmt->i_format = VLC_CODEC_SPDIFL;
            fmt->i_bytes_per_frame = 4;
            fmt->i_frame_length = 1;
            break;
        case VLC_CODEC_DTS:
        case VLC_CODEC_TRUEHD:
        case VLC_CODEC_MLP:
            fmt->i_format = VLC_CODEC_SPDIFL;
            fmt->i_rate = 768000;
            fmt->i_bytes_per_frame = 16;
            fmt->i_frame_length = 1;
            break;
        default:
            assert(AOUT_FMT_LINEAR(fmt));
            assert(aout_FormatNbChannels(fmt) > 0);
            fmt->i_format = HAVE_FPU ? VLC_CODEC_FL32 : VLC_CODEC_S16N;
            fmt->channel_type = AUDIO_CHANNEL_TYPE_BITMAP;
            break;
    }

    return VLC_SUCCESS;
}