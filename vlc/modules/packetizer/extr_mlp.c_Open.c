#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_8__ {scalar_t__ i_rate; } ;
struct TYPE_9__ {scalar_t__ i_codec; TYPE_2__ audio; } ;
struct TYPE_7__ {scalar_t__ i_codec; } ;
struct TYPE_10__ {int /*<<< orphan*/ * pf_get_cc; int /*<<< orphan*/  pf_flush; int /*<<< orphan*/  pf_packetize; TYPE_3__ fmt_out; TYPE_1__ fmt_in; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ decoder_t ;
struct TYPE_11__ {int b_mlp; int b_discontinuity; int /*<<< orphan*/  bytestream; int /*<<< orphan*/  end_date; int /*<<< orphan*/  i_state; } ;
typedef  TYPE_5__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Flush ; 
 int /*<<< orphan*/  Packetize ; 
 int /*<<< orphan*/  STATE_NOSYNC ; 
 scalar_t__ VLC_CODEC_MLP ; 
 scalar_t__ VLC_CODEC_TRUEHD ; 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  block_BytestreamInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,int,int) ; 
 TYPE_5__* malloc (int) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    decoder_t *p_dec = (decoder_t*)p_this;
    decoder_sys_t *p_sys;

    if( p_dec->fmt_in.i_codec != VLC_CODEC_MLP &&
        p_dec->fmt_in.i_codec != VLC_CODEC_TRUEHD )
        return VLC_EGENERIC;

    /* */
    p_dec->p_sys = p_sys = malloc( sizeof(*p_sys) );
    if( !p_sys )
        return VLC_ENOMEM;

    /* */
    p_sys->i_state = STATE_NOSYNC;
    date_Init( &p_sys->end_date, 1, 1 );

    block_BytestreamInit( &p_sys->bytestream );
    p_sys->b_mlp = false;
    p_sys->b_discontinuity = false;

    /* Set output properties (Passthrough only) */
    p_dec->fmt_out.i_codec = p_dec->fmt_in.i_codec;
    p_dec->fmt_out.audio.i_rate = 0;

    /* Set callback */
    p_dec->pf_packetize = Packetize;
    p_dec->pf_flush     = Flush;
    p_dec->pf_get_cc    = NULL;
    return VLC_SUCCESS;
}