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
typedef  int /*<<< orphan*/  vlc_a52_header_t ;
struct TYPE_7__ {scalar_t__ i_rate; } ;
struct TYPE_8__ {int i_codec; TYPE_2__ audio; } ;
struct TYPE_6__ {int i_codec; TYPE_2__ audio; } ;
struct TYPE_9__ {int /*<<< orphan*/ * pf_get_cc; int /*<<< orphan*/  pf_flush; int /*<<< orphan*/  pf_packetize; TYPE_3__ fmt_out; TYPE_1__ fmt_in; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ decoder_t ;
struct TYPE_10__ {int b_discontuinity; int /*<<< orphan*/  bytestream; int /*<<< orphan*/  frame; int /*<<< orphan*/  i_prev_bytestream_pts; int /*<<< orphan*/  end_date; int /*<<< orphan*/  i_state; } ;
typedef  TYPE_5__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  PacketizeBlock ; 
 int /*<<< orphan*/  PacketizeFlush ; 
 int /*<<< orphan*/  STATE_NOSYNC ; 
#define  VLC_CODEC_A52 129 
#define  VLC_CODEC_EAC3 128 
 int VLC_EGENERIC ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_BytestreamInit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ malloc (int) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int Open( vlc_object_t *p_this )
{
    decoder_t *p_dec = (decoder_t*)p_this;
    decoder_sys_t *p_sys;

    switch( p_dec->fmt_in.i_codec )
    {
    case VLC_CODEC_EAC3:
    case VLC_CODEC_A52:
        break;
    default:
        return VLC_EGENERIC;
    }

    /* Allocate the memory needed to store the decoder's structure */
    if( ( p_dec->p_sys = p_sys =
          (decoder_sys_t *)malloc(sizeof(decoder_sys_t)) ) == NULL )
        return VLC_ENOMEM;

    /* Misc init */
    p_sys->i_state = STATE_NOSYNC;
    date_Set( &p_sys->end_date, VLC_TICK_INVALID );
    p_sys->b_discontuinity = false;
    p_sys->i_prev_bytestream_pts = VLC_TICK_INVALID;
    memset(&p_sys->frame, 0, sizeof(vlc_a52_header_t));

    block_BytestreamInit( &p_sys->bytestream );

    /* Set output properties (Passthrough ONLY) */
    p_dec->fmt_out.i_codec = p_dec->fmt_in.i_codec;
    p_dec->fmt_out.audio = p_dec->fmt_in.audio;
    p_dec->fmt_out.audio.i_rate = 0;

    /* Set callback */
    p_dec->pf_packetize = PacketizeBlock;
    p_dec->pf_flush     = PacketizeFlush;
    p_dec->pf_get_cc    = NULL;
    return VLC_SUCCESS;
}