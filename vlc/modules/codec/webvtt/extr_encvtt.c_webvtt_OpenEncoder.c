#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_3__ {scalar_t__ i_codec; int /*<<< orphan*/  i_cat; } ;
struct TYPE_4__ {TYPE_1__ fmt_out; int /*<<< orphan*/  pf_encode_sub; int /*<<< orphan*/ * p_sys; } ;
typedef  TYPE_2__ encoder_t ;

/* Variables and functions */
 int /*<<< orphan*/  Encode ; 
 int /*<<< orphan*/  SPU_ES ; 
 scalar_t__ VLC_CODEC_WEBVTT ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 

int webvtt_OpenEncoder( vlc_object_t *p_this )
{
    encoder_t *p_enc = (encoder_t *)p_this;

    if( p_enc->fmt_out.i_codec != VLC_CODEC_WEBVTT )
        return VLC_EGENERIC;

    p_enc->p_sys = NULL;

    p_enc->pf_encode_sub = Encode;
    p_enc->fmt_out.i_cat = SPU_ES;
    return VLC_SUCCESS;
}