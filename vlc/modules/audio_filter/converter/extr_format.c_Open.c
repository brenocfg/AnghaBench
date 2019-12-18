#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_8__ {int /*<<< orphan*/  i_bitspersample; } ;
struct TYPE_7__ {scalar_t__ i_codec; TYPE_4__ audio; } ;
struct TYPE_6__ {int /*<<< orphan*/ * pf_audio_filter; TYPE_2__ fmt_out; TYPE_2__ fmt_in; } ;
typedef  TYPE_1__ filter_t ;
typedef  TYPE_2__ es_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  AOUT_FMTS_SIMILAR (TYPE_4__*,TYPE_4__*) ; 
 int /*<<< orphan*/ * FindConversion (scalar_t__,scalar_t__) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,char*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int Open(vlc_object_t *object)
{
    filter_t     *filter = (filter_t *)object;

    const es_format_t *src = &filter->fmt_in;
    es_format_t       *dst = &filter->fmt_out;

    if (!AOUT_FMTS_SIMILAR(&src->audio, &dst->audio))
        return VLC_EGENERIC;
    if (src->i_codec == dst->i_codec)
        return VLC_EGENERIC;

    filter->pf_audio_filter = FindConversion(src->i_codec, dst->i_codec);
    if (filter->pf_audio_filter == NULL)
        return VLC_EGENERIC;

    msg_Dbg(filter, "%4.4s->%4.4s, bits per sample: %i->%i",
            (char *)&src->i_codec, (char *)&dst->i_codec,
            src->audio.i_bitspersample, dst->audio.i_bitspersample);
    return VLC_SUCCESS;
}