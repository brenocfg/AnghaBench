#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_8__ {scalar_t__ i_format; scalar_t__ i_channels; } ;
struct TYPE_9__ {TYPE_3__ audio; } ;
struct TYPE_6__ {scalar_t__ i_format; scalar_t__ i_channels; } ;
struct TYPE_7__ {TYPE_1__ audio; } ;
struct TYPE_10__ {int /*<<< orphan*/  pf_audio_filter; int /*<<< orphan*/ * p_sys; TYPE_4__ fmt_in; TYPE_2__ fmt_out; } ;
typedef  TYPE_5__ filter_t ;
typedef  int /*<<< orphan*/  SRC_STATE ;

/* Variables and functions */
 int /*<<< orphan*/  Resample ; 
 scalar_t__ VLC_CODEC_FL32 ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * src_new (int,scalar_t__,int*) ; 
 int /*<<< orphan*/  src_strerror (int) ; 
 int var_InheritInteger (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int OpenResampler (vlc_object_t *obj)
{
    filter_t *filter = (filter_t *)obj;

    /* Only float->float */
    if (filter->fmt_in.audio.i_format != VLC_CODEC_FL32
     || filter->fmt_out.audio.i_format != VLC_CODEC_FL32
    /* No channels remapping */
     || filter->fmt_in.audio.i_channels != filter->fmt_out.audio.i_channels )
        return VLC_EGENERIC;

    int type = var_InheritInteger (obj, "src-converter-type");
    int err;

    SRC_STATE *s = src_new (type, filter->fmt_in.audio.i_channels, &err);
    if (s == NULL)
    {
        msg_Err (obj, "cannot initialize resampler: %s", src_strerror (err));
        return VLC_EGENERIC;
    }

    filter->p_sys = s;
    filter->pf_audio_filter = Resample;
    return VLC_SUCCESS;
}