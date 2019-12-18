#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  vlc_clock_t ;
struct TYPE_19__ {scalar_t__ i_physical_channels; scalar_t__ i_channels; int /*<<< orphan*/  i_format; } ;
struct TYPE_17__ {TYPE_5__ audio; int /*<<< orphan*/  i_codec; } ;
struct TYPE_16__ {TYPE_5__ audio; int /*<<< orphan*/  i_codec; } ;
struct TYPE_15__ {int /*<<< orphan*/ * sys; } ;
struct TYPE_18__ {int /*<<< orphan*/ * pf_audio_filter; int /*<<< orphan*/ * p_module; TYPE_3__ fmt_out; TYPE_2__ fmt_in; int /*<<< orphan*/ * p_cfg; TYPE_1__ owner; } ;
typedef  TYPE_4__ filter_t ;
typedef  int /*<<< orphan*/  config_chain_t ;
typedef  TYPE_5__ audio_sample_format_t ;

/* Variables and functions */
 int AOUT_FMTS_IDENTICAL (TYPE_5__*,TYPE_5__ const*) ; 
 scalar_t__ aout_FormatNbChannels (TYPE_5__ const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * module_need (TYPE_4__*,char const*,char const*,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 TYPE_4__* vlc_custom_create (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/  vlc_object_delete (TYPE_4__*) ; 

__attribute__((used)) static filter_t *CreateFilter(vlc_object_t *obj, vlc_clock_t *clock,
                              const char *type, const char *name,
                              const audio_sample_format_t *infmt,
                              const audio_sample_format_t *outfmt,
                              config_chain_t *cfg, bool const_fmt)
{
    filter_t *filter = vlc_custom_create (obj, sizeof (*filter), type);
    if (unlikely(filter == NULL))
        return NULL;

    filter->owner.sys = clock;
    filter->p_cfg = cfg;
    filter->fmt_in.audio = *infmt;
    filter->fmt_in.i_codec = infmt->i_format;
    filter->fmt_out.audio = *outfmt;
    filter->fmt_out.i_codec = outfmt->i_format;

#ifndef NDEBUG
    /* Assure that infmt/oufmt are well prepared and that channels
     * configurations are valid*/
    if( infmt->i_physical_channels != 0 )
        assert( aout_FormatNbChannels( infmt ) == infmt->i_channels );
    if( outfmt->i_physical_channels != 0 )
        assert( aout_FormatNbChannels( outfmt ) == outfmt->i_channels );
#endif

    filter->p_module = module_need (filter, type, name, false);

#ifndef NDEBUG
    if (filter->p_module == NULL || const_fmt)
    {
        /* If probing failed, formats shall not have been modified. */
        assert (AOUT_FMTS_IDENTICAL(&filter->fmt_in.audio, infmt));
        assert (AOUT_FMTS_IDENTICAL(&filter->fmt_out.audio, outfmt));
    }
#endif

    if (filter->p_module == NULL)
    {
        vlc_object_delete(filter);
        filter = NULL;
    }
    else
        assert (filter->pf_audio_filter != NULL);
    return filter;
}