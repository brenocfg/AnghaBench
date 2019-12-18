#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int i_rate; int i_bitspersample; } ;
struct TYPE_9__ {TYPE_1__ audio; scalar_t__ i_codec; } ;
struct TYPE_10__ {scalar_t__ i_codec; } ;
struct TYPE_11__ {int /*<<< orphan*/  pf_flush; int /*<<< orphan*/  pf_decode; TYPE_2__ fmt_out; int /*<<< orphan*/  pf_packetize; TYPE_5__* p_sys; TYPE_3__ fmt_in; } ;
typedef  TYPE_4__ decoder_t ;
struct TYPE_12__ {int /*<<< orphan*/  end_date; } ;
typedef  TYPE_5__ decoder_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  Decode ; 
 int /*<<< orphan*/  Flush ; 
 int /*<<< orphan*/  Packetize ; 
 scalar_t__ VLC_CODEC_302M ; 
 scalar_t__ VLC_CODEC_S16N ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,int,int) ; 
 TYPE_5__* malloc (int) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int Open( decoder_t *p_dec, bool b_packetizer )
{
    decoder_sys_t *p_sys;

    if( p_dec->fmt_in.i_codec != VLC_CODEC_302M )
        return VLC_EGENERIC;

    /* Allocate the memory needed to store the decoder's structure */
    p_dec->p_sys = p_sys = malloc( sizeof(decoder_sys_t) );

    if( unlikely( !p_sys ) )
        return VLC_EGENERIC;

    /* Misc init */
    date_Init( &p_sys->end_date, 48000, 1 );

    /* Set output properties */
    p_dec->fmt_out.audio.i_rate = 48000;

    /* Set callback */
    if( b_packetizer )
    {
        p_dec->fmt_out.i_codec = VLC_CODEC_302M;

        p_dec->pf_packetize    = Packetize;
    }
    else
    {
        p_dec->fmt_out.i_codec = VLC_CODEC_S16N;
        p_dec->fmt_out.audio.i_bitspersample = 16;

        p_dec->pf_decode    = Decode;
    }
    p_dec->pf_flush            = Flush;
    return VLC_SUCCESS;
}