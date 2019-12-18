#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_10__ {scalar_t__ i_codec; } ;
struct TYPE_11__ {scalar_t__ i_codec; } ;
struct TYPE_12__ {TYPE_2__ fmt_out; int /*<<< orphan*/  pf_decode; TYPE_5__* p_sys; TYPE_3__ fmt_in; } ;
typedef  TYPE_4__ decoder_t ;
struct TYPE_13__ {TYPE_1__* groups; } ;
typedef  TYPE_5__ decoder_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/  p_segment; int /*<<< orphan*/ * pp_segment_last; } ;

/* Variables and functions */
 int /*<<< orphan*/  Decode ; 
 int ParseGSI (TYPE_4__*,TYPE_5__*) ; 
 size_t STL_GROUPS_MAX ; 
 scalar_t__ VLC_CODEC_EBU_STL ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_5__* calloc (int,int) ; 

__attribute__((used)) static int Open(vlc_object_t *object)
{
    decoder_t *dec = (decoder_t*)object;

    if (dec->fmt_in.i_codec != VLC_CODEC_EBU_STL)
        return VLC_EGENERIC;

    decoder_sys_t *sys = calloc(1, sizeof(*sys));
    if (!sys)
        return VLC_ENOMEM;

    int rc = ParseGSI(dec, sys);
    if (VLC_SUCCESS != rc)
        return rc;

    for(size_t i=0; i<=STL_GROUPS_MAX; i++)
        sys->groups[i].pp_segment_last = &sys->groups[i].p_segment;

    dec->p_sys = sys;
    dec->pf_decode = Decode;
    dec->fmt_out.i_codec = 0;
    return VLC_SUCCESS;
}