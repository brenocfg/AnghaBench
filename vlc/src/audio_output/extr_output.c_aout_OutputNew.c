#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_fourcc_t ;
struct TYPE_20__ {scalar_t__ channel_type; unsigned int i_channels; scalar_t__ i_format; scalar_t__ i_physical_channels; int i_bitspersample; scalar_t__ i_bytes_per_frame; scalar_t__ i_frame_length; } ;
typedef  TYPE_2__ audio_sample_format_t ;
struct TYPE_19__ {int headphones; } ;
struct TYPE_21__ {int (* start ) (TYPE_3__*,TYPE_2__*) ;scalar_t__ pause; scalar_t__ time_get; scalar_t__ play; scalar_t__ flush; TYPE_1__ current_sink_info; } ;
typedef  TYPE_3__ audio_output_t ;
typedef  scalar_t__ audio_channel_type_t ;
struct TYPE_22__ {scalar_t__ requested_stereo_mode; int /*<<< orphan*/  lock; int /*<<< orphan*/  input_profile; int /*<<< orphan*/  filters_cfg; TYPE_2__ filter_format; TYPE_2__ mixer_format; } ;
typedef  TYPE_4__ aout_owner_t ;
typedef  int /*<<< orphan*/  aout_filters_cfg_t ;

/* Variables and functions */
 scalar_t__ AOUT_CHANS_7_1 ; 
 scalar_t__ AOUT_CHANS_STEREO ; 
 scalar_t__ AOUT_CHAN_CENTER ; 
 scalar_t__ AOUT_FMT_LINEAR (TYPE_2__*) ; 
 scalar_t__ AOUT_VAR_CHAN_LEFT ; 
 scalar_t__ AOUT_VAR_CHAN_RIGHT ; 
 int ARRAY_SIZE (scalar_t__*) ; 
 scalar_t__ AUDIO_CHANNEL_TYPE_AMBISONICS ; 
 scalar_t__ AUDIO_CHANNEL_TYPE_BITMAP ; 
#define  VLC_CODEC_A52 129 
#define  VLC_CODEC_DTS 128 
 scalar_t__ VLC_CODEC_DTSHD ; 
 scalar_t__ VLC_CODEC_EAC3 ; 
 scalar_t__ VLC_CODEC_FL32 ; 
 scalar_t__ VLC_CODEC_S16N ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ aout_FormatNbChannels (TYPE_2__*) ; 
 int /*<<< orphan*/  aout_FormatPrepare (TYPE_2__*) ; 
 int /*<<< orphan*/  aout_FormatPrint (TYPE_3__*,char*,TYPE_2__*) ; 
 int /*<<< orphan*/  aout_PrepareStereoMode (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ *,scalar_t__,unsigned int) ; 
 int /*<<< orphan*/  aout_SetWavePhysicalChannels (TYPE_2__*) ; 
 TYPE_4__* aout_owner (TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*) ; 
 int stub1 (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int aout_OutputNew (audio_output_t *aout)
{
    aout_owner_t *owner = aout_owner (aout);
    audio_sample_format_t *fmt = &owner->mixer_format;
    audio_sample_format_t *filter_fmt = &owner->filter_format;
    aout_filters_cfg_t *filters_cfg = &owner->filters_cfg;

    audio_channel_type_t input_chan_type = fmt->channel_type;
    unsigned i_nb_input_channels = fmt->i_channels;
    vlc_fourcc_t formats[] = {
        fmt->i_format, 0, 0
    };

    /* Ideally, the audio filters would be created before the audio output,
     * and the ideal audio format would be the output of the filters chain.
     * But that scheme would not really play well with digital pass-through. */
    if (AOUT_FMT_LINEAR(fmt))
    {
        if (fmt->channel_type == AUDIO_CHANNEL_TYPE_BITMAP
         && aout_FormatNbChannels(fmt) == 0)
        {
            /* The output channel map is unknown, use the WAVE one. */
            assert(fmt->i_channels > 0);
            aout_SetWavePhysicalChannels(fmt);
        }

        if (fmt->channel_type == AUDIO_CHANNEL_TYPE_AMBISONICS)
        {
            /* Set the maximum of channels to render ambisonics contents. The
             * aout module will still be free to select less channels in order
             * to respect the sink setup. */
            fmt->i_physical_channels = AOUT_CHANS_7_1;
        }

        /* Try to stay in integer domain if possible for no/slow FPU. */
        fmt->i_format = (fmt->i_bitspersample > 16) ? VLC_CODEC_FL32
                                                    : VLC_CODEC_S16N;

        if (fmt->i_physical_channels == AOUT_CHANS_STEREO
         && (owner->requested_stereo_mode == AOUT_VAR_CHAN_LEFT
          || owner->requested_stereo_mode == AOUT_VAR_CHAN_RIGHT))
            fmt->i_physical_channels = AOUT_CHAN_CENTER;

        aout_FormatPrepare (fmt);
        assert (aout_FormatNbChannels(fmt) > 0);
    }
    else
    {
        switch (fmt->i_format)
        {
            case VLC_CODEC_DTS:
                if (owner->input_profile > 0)
                {
                    assert(ARRAY_SIZE(formats) >= 3);
                    /* DTSHD can be played as DTSHD or as DTS */
                    formats[0] = VLC_CODEC_DTSHD;
                    formats[1] = VLC_CODEC_DTS;
                }
                break;
            case VLC_CODEC_A52:
                if (owner->input_profile > 0)
                {
                    assert(ARRAY_SIZE(formats) >= 3);
                    formats[0] = VLC_CODEC_EAC3;
                    formats[1] = VLC_CODEC_A52;
                }
                break;
            default:
                break;
        }
    }

    aout->current_sink_info.headphones = false;

    vlc_mutex_lock(&owner->lock);
    int ret = VLC_EGENERIC;
    for (size_t i = 0; formats[i] != 0 && ret != VLC_SUCCESS; ++i)
    {
        filter_fmt->i_format = fmt->i_format = formats[i];
        ret = aout->start(aout, fmt);
    }
    vlc_mutex_unlock(&owner->lock);
    if (ret)
    {
        msg_Err (aout, "module not functional");
        return -1;
    }
    assert(aout->flush && aout->play && aout->time_get && aout->pause);

    aout_PrepareStereoMode (aout, fmt, filters_cfg, input_chan_type,
                            i_nb_input_channels);

    aout_FormatPrepare (fmt);
    assert (fmt->i_bytes_per_frame > 0 && fmt->i_frame_length > 0);
    aout_FormatPrint (aout, "output", fmt);
    return 0;
}