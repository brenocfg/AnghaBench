#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_10__ {scalar_t__ i_rate; int i_channels; int i_physical_channels; } ;
struct TYPE_11__ {TYPE_3__ audio; int /*<<< orphan*/  i_codec; } ;
struct TYPE_8__ {int i_bitspersample; int i_channels; scalar_t__ i_rate; } ;
struct TYPE_9__ {scalar_t__ i_codec; TYPE_1__ audio; } ;
struct TYPE_12__ {int /*<<< orphan*/  pf_flush; int /*<<< orphan*/  pf_decode; TYPE_4__ fmt_out; TYPE_2__ fmt_in; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ decoder_t ;
struct TYPE_13__ {int is_pal; int is_12bit; int* shuffle; int /*<<< orphan*/  end_date; } ;
typedef  TYPE_6__ decoder_sys_t ;

/* Variables and functions */
 int AOUT_CHAN_LEFT ; 
 int AOUT_CHAN_RIGHT ; 
 int /*<<< orphan*/  DecodeAudio ; 
 int /*<<< orphan*/  Flush ; 
 int /*<<< orphan*/  VLC_CODEC_S16N ; 
 scalar_t__ VLC_CODEC_ULEAD_DV_AUDIO_NTSC ; 
 scalar_t__ VLC_CODEC_ULEAD_DV_AUDIO_PAL ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,scalar_t__,int) ; 
 TYPE_6__* malloc (int) ; 

__attribute__((used)) static int Open(vlc_object_t *object)
{
    decoder_t *dec = (decoder_t*)object;

    if (dec->fmt_in.i_codec != VLC_CODEC_ULEAD_DV_AUDIO_NTSC &&
        dec->fmt_in.i_codec != VLC_CODEC_ULEAD_DV_AUDIO_PAL)
        return VLC_EGENERIC;
    if (dec->fmt_in.audio.i_bitspersample != 12 && dec->fmt_in.audio.i_bitspersample != 16)
        return VLC_EGENERIC;
    if (dec->fmt_in.audio.i_channels != 2)
        return VLC_EGENERIC;
    if (dec->fmt_in.audio.i_rate <= 0)
        return VLC_EGENERIC;

    decoder_sys_t *sys = dec->p_sys = malloc(sizeof(*sys));
    if (!sys)
        return VLC_ENOMEM;

    sys->is_pal = dec->fmt_in.i_codec == VLC_CODEC_ULEAD_DV_AUDIO_PAL;
    sys->is_12bit = dec->fmt_in.audio.i_bitspersample == 12;

    date_Init(&sys->end_date, dec->fmt_in.audio.i_rate, 1);

    for (unsigned i = 0; i < sizeof(sys->shuffle) / sizeof(*sys->shuffle); i++) {
        const unsigned a = sys->is_pal ? 18 : 15;
        const unsigned b = 3 * a;
        sys->shuffle[i] = 80 * ((21 * (i % 3) + 9 * (i / 3) + ((i / a) % 3)) % b) +
                          (2 + sys->is_12bit) * (i / b) + 8;
    }

    dec->fmt_out.i_codec = VLC_CODEC_S16N;
    dec->fmt_out.audio.i_rate = dec->fmt_in.audio.i_rate;
    dec->fmt_out.audio.i_channels = 2;
    dec->fmt_out.audio.i_physical_channels = AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT;

    dec->pf_decode = DecodeAudio;
    dec->pf_flush  = Flush;

    return VLC_SUCCESS;
}