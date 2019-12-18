#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_6__ {int /*<<< orphan*/  i_codec; } ;
struct TYPE_7__ {scalar_t__ i_codec; } ;
struct TYPE_8__ {int /*<<< orphan*/  pf_flush; int /*<<< orphan*/  pf_decode; TYPE_1__ fmt_out; TYPE_4__* p_sys; TYPE_2__ fmt_in; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_9__ {int b_has_headers; int /*<<< orphan*/ * p_st; int /*<<< orphan*/  end_date; } ;
typedef  TYPE_4__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  DecodeAudio ; 
 int /*<<< orphan*/  Flush ; 
 int /*<<< orphan*/  VLC_CODEC_FL32 ; 
 scalar_t__ VLC_CODEC_OPUS ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_4__* malloc (int) ; 

__attribute__((used)) static int OpenDecoder( vlc_object_t *p_this )
{
    decoder_t *p_dec = (decoder_t*)p_this;
    decoder_sys_t *p_sys;

    if( p_dec->fmt_in.i_codec != VLC_CODEC_OPUS )
        return VLC_EGENERIC;

    /* Allocate the memory needed to store the decoder's structure */
    if( ( p_dec->p_sys = p_sys = malloc(sizeof(decoder_sys_t)) ) == NULL )
        return VLC_ENOMEM;
    p_sys->b_has_headers = false;

    date_Set( &p_sys->end_date, VLC_TICK_INVALID );

    /* Set output properties */
    p_dec->fmt_out.i_codec = VLC_CODEC_FL32;

    p_dec->pf_decode    = DecodeAudio;
    p_dec->pf_flush     = Flush;

    p_sys->p_st = NULL;

    return VLC_SUCCESS;
}