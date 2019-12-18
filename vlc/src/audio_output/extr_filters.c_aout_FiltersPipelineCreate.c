#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  filter_t ;
typedef  int /*<<< orphan*/  config_chain_t ;
struct TYPE_13__ {scalar_t__ i_physical_channels; scalar_t__ i_chan_mode; scalar_t__ channel_type; scalar_t__ i_format; scalar_t__ i_rate; } ;
typedef  TYPE_1__ audio_sample_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOUT_FMT_LINEAR (TYPE_1__*) ; 
 int /*<<< orphan*/ * CreateFilter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * FindConverter (int /*<<< orphan*/ *,TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/ * TryFormat (int /*<<< orphan*/ *,scalar_t__,TYPE_1__*) ; 
 scalar_t__ VLC_CODEC_FL32 ; 
 int /*<<< orphan*/  _ (char*) ; 
 int /*<<< orphan*/  aout_FiltersPipelineDestroy (int /*<<< orphan*/ **,unsigned int) ; 
 int /*<<< orphan*/  aout_FormatPrepare (TYPE_1__*) ; 
 int /*<<< orphan*/  aout_FormatsPrint (int /*<<< orphan*/ *,char*,TYPE_1__ const*,TYPE_1__ const*) ; 
 int /*<<< orphan*/  config_ChainDestroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  config_ChainParseOptions (int /*<<< orphan*/ **,char*) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  vlc_dialog_display_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int aout_FiltersPipelineCreate(vlc_object_t *obj, filter_t **filters,
                                      unsigned *count, unsigned max,
                                 const audio_sample_format_t *restrict infmt,
                                 const audio_sample_format_t *restrict outfmt,
                                 bool headphones)
{
    aout_FormatsPrint (obj, "conversion:", infmt, outfmt);
    max -= *count;
    filters += *count;

    /* There is a lot of second guessing on what the conversion plugins can
     * and cannot do. This seems hardly avoidable, the conversion problem need
     * to be reduced somehow. */
    audio_sample_format_t input = *infmt;
    unsigned n = 0;

    if (!AOUT_FMT_LINEAR(&input))
    {
        msg_Err(obj, "Can't convert non linear input");
        return -1;
    }

    /* Remix channels */
    if (infmt->i_physical_channels != outfmt->i_physical_channels
     || infmt->i_chan_mode != outfmt->i_chan_mode
     || infmt->channel_type != outfmt->channel_type)
    {   /* Remixing currently requires FL32... TODO: S16N */
        if (input.i_format != VLC_CODEC_FL32)
        {
            if (n == max)
                goto overflow;

            filter_t *f = TryFormat (obj, VLC_CODEC_FL32, &input);
            if (f == NULL)
            {
                msg_Err (obj, "cannot find %s for conversion pipeline",
                         "pre-mix converter");
                goto error;
            }

            filters[n++] = f;
        }

        if (n == max)
            goto overflow;

        audio_sample_format_t output;
        output.i_format = input.i_format;
        output.i_rate = input.i_rate;
        output.i_physical_channels = outfmt->i_physical_channels;
        output.channel_type = outfmt->channel_type;
        output.i_chan_mode = outfmt->i_chan_mode;
        aout_FormatPrepare (&output);

        const char *filter_type =
            infmt->channel_type != outfmt->channel_type ?
            "audio renderer" : "audio converter";

        config_chain_t *cfg = NULL;
        if (headphones)
            config_ChainParseOptions(&cfg, "{headphones=true}");
        filter_t *f = CreateFilter(obj, NULL, filter_type, NULL,
                                   &input, &output, cfg, true);
        if (cfg)
            config_ChainDestroy(cfg);

        if (f == NULL)
        {
            msg_Err (obj, "cannot find %s for conversion pipeline",
                     "remixer");
            goto error;
        }

        input = output;
        filters[n++] = f;
    }

    /* Resample */
    if (input.i_rate != outfmt->i_rate)
    {   /* Resampling works with any linear format, but may be ugly. */
        if (n == max)
            goto overflow;

        audio_sample_format_t output = input;
        output.i_rate = outfmt->i_rate;

        filter_t *f = FindConverter (obj, &input, &output);
        if (f == NULL)
        {
            msg_Err (obj, "cannot find %s for conversion pipeline",
                     "resampler");
            goto error;
        }

        input = output;
        filters[n++] = f;
    }

    /* Format */
    if (input.i_format != outfmt->i_format)
    {
        if (max == 0)
            goto overflow;

        filter_t *f = TryFormat (obj, outfmt->i_format, &input);
        if (f == NULL)
        {
            msg_Err (obj, "cannot find %s for conversion pipeline",
                     "post-mix converter");
            goto error;
        }
        filters[n++] = f;
    }

    msg_Dbg (obj, "conversion pipeline complete");
    *count += n;
    return 0;

overflow:
    msg_Err (obj, "maximum of %u conversion filters reached", max);
    vlc_dialog_display_error (obj, _("Audio filtering failed"),
        _("The maximum number of filters (%u) was reached."), max);
error:
    aout_FiltersPipelineDestroy (filters, n);
    return -1;
}