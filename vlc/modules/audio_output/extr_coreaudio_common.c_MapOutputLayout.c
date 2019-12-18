#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  unsigned int const uint32_t ;
typedef  int /*<<< orphan*/  i_auhal_channel_mapping ;
struct TYPE_13__ {unsigned int i_physical_channels; } ;
typedef  TYPE_2__ audio_sample_format_t ;
typedef  int /*<<< orphan*/  audio_output_t ;
struct TYPE_14__ {scalar_t__ mChannelLayoutTag; int mNumberChannelDescriptions; TYPE_1__* mChannelDescriptions; } ;
struct TYPE_12__ {size_t mChannelLabel; } ;
typedef  TYPE_3__ AudioChannelLayout ;
typedef  size_t const AudioChannelLabel ;

/* Variables and functions */
 void* AOUT_CHANS_STEREO ; 
#define  AOUT_CHAN_CENTER 145 
#define  AOUT_CHAN_LEFT 144 
#define  AOUT_CHAN_LFE 143 
#define  AOUT_CHAN_MIDDLELEFT 142 
#define  AOUT_CHAN_MIDDLERIGHT 141 
#define  AOUT_CHAN_REARCENTER 140 
#define  AOUT_CHAN_REARLEFT 139 
#define  AOUT_CHAN_REARRIGHT 138 
#define  AOUT_CHAN_RIGHT 137 
 TYPE_3__* GetLayoutDescription (int /*<<< orphan*/ *,TYPE_3__ const*) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int aout_FormatNbChannels (TYPE_2__*) ; 
 int /*<<< orphan*/  aout_FormatPrepare (TYPE_2__*) ; 
 int aout_FormatPrintChannels (TYPE_2__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
#define  kAudioChannelLabel_Center 136 
#define  kAudioChannelLabel_CenterSurround 135 
#define  kAudioChannelLabel_LFEScreen 134 
#define  kAudioChannelLabel_Left 133 
#define  kAudioChannelLabel_LeftSurround 132 
#define  kAudioChannelLabel_RearSurroundLeft 131 
#define  kAudioChannelLabel_RearSurroundRight 130 
#define  kAudioChannelLabel_Right 129 
#define  kAudioChannelLabel_RightSurround 128 
 scalar_t__ kAudioChannelLayoutTag_UseChannelDescriptions ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 

__attribute__((used)) static int
MapOutputLayout(audio_output_t *p_aout, audio_sample_format_t *fmt,
                const AudioChannelLayout *outlayout, bool *warn_configuration)
{
    /* Fill VLC physical_channels from output layout */
    fmt->i_physical_channels = 0;
    uint32_t i_original = fmt->i_physical_channels;
    AudioChannelLayout *reslayout = NULL;

    if (outlayout == NULL)
    {
        msg_Dbg(p_aout, "not output layout, default to Stereo");
        fmt->i_physical_channels = AOUT_CHANS_STEREO;
        goto end;
    }

    if (outlayout->mChannelLayoutTag !=
        kAudioChannelLayoutTag_UseChannelDescriptions)
    {
        reslayout = GetLayoutDescription(p_aout, outlayout);
        if (reslayout == NULL)
            return VLC_EGENERIC;
        outlayout = reslayout;
    }

    if (i_original == AOUT_CHAN_CENTER
     || outlayout->mNumberChannelDescriptions < 2)
    {
        /* We only need Mono or cannot output more than 1 channel */
        fmt->i_physical_channels = AOUT_CHAN_CENTER;
        msg_Dbg(p_aout, "output layout of AUHAL has 1 channel");
    }
    else if (i_original == (AOUT_CHAN_LEFT | AOUT_CHAN_RIGHT)
          || outlayout->mNumberChannelDescriptions < 3)
    {
        /* We only need Stereo or cannot output more than 2 channels */
        fmt->i_physical_channels = AOUT_CHANS_STEREO;
        msg_Dbg(p_aout, "output layout of AUHAL is Stereo");
    }
    else
    {
        assert(outlayout->mNumberChannelDescriptions > 0);

        msg_Dbg(p_aout, "output layout of AUHAL has %i channels",
                outlayout->mNumberChannelDescriptions);

        /* maps auhal channels to vlc ones */
        static const unsigned i_auhal_channel_mapping[] = {
            [kAudioChannelLabel_Left]           = AOUT_CHAN_LEFT,
            [kAudioChannelLabel_Right]          = AOUT_CHAN_RIGHT,
            [kAudioChannelLabel_Center]         = AOUT_CHAN_CENTER,
            [kAudioChannelLabel_LFEScreen]      = AOUT_CHAN_LFE,
            [kAudioChannelLabel_LeftSurround]   = AOUT_CHAN_REARLEFT,
            [kAudioChannelLabel_RightSurround]  = AOUT_CHAN_REARRIGHT,
            /* needs to be swapped with rear */
            [kAudioChannelLabel_RearSurroundLeft]  = AOUT_CHAN_MIDDLELEFT,
            /* needs to be swapped with rear */
            [kAudioChannelLabel_RearSurroundRight] = AOUT_CHAN_MIDDLERIGHT,
            [kAudioChannelLabel_CenterSurround] = AOUT_CHAN_REARCENTER
        };
        static const size_t i_auhal_size = sizeof(i_auhal_channel_mapping)
                                         / sizeof(i_auhal_channel_mapping[0]);

        /* We want more than stereo and we can do that */
        for (unsigned i = 0; i < outlayout->mNumberChannelDescriptions; i++)
        {
            AudioChannelLabel chan =
                outlayout->mChannelDescriptions[i].mChannelLabel;
#ifndef NDEBUG
            msg_Dbg(p_aout, "this is channel: %d", (int) chan);
#endif
            if (chan < i_auhal_size && i_auhal_channel_mapping[chan] > 0)
                fmt->i_physical_channels |= i_auhal_channel_mapping[chan];
            else
                msg_Dbg(p_aout, "found nonrecognized channel %d at index "
                        "%d", chan, i);
        }
        if (fmt->i_physical_channels == 0)
        {
            fmt->i_physical_channels = AOUT_CHANS_STEREO;
            if (warn_configuration)
                *warn_configuration = true;
        }

    }

end:
    free(reslayout);
    aout_FormatPrepare(fmt);

    msg_Dbg(p_aout, "selected %d physical channels for device output",
            aout_FormatNbChannels(fmt));
    msg_Dbg(p_aout, "VLC will output: %s", aout_FormatPrintChannels(fmt));

    return VLC_SUCCESS;
}