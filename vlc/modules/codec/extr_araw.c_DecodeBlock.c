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
struct TYPE_15__ {unsigned int i_channels; } ;
struct TYPE_16__ {TYPE_1__ audio; } ;
struct TYPE_17__ {TYPE_2__ fmt_in; TYPE_4__* p_sys; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_18__ {int framebits; int /*<<< orphan*/  end_date; int /*<<< orphan*/  (* decode ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ;} ;
typedef  TYPE_4__ decoder_sys_t ;
struct TYPE_19__ {int i_flags; scalar_t__ i_pts; int i_buffer; unsigned int i_nb_samples; scalar_t__ i_length; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_5__ block_t ;

/* Variables and functions */
 int BLOCK_FLAG_CORRUPTED ; 
 int BLOCK_FLAG_DISCONTINUITY ; 
 int /*<<< orphan*/  Flush (TYPE_3__*) ; 
 int VLCDEC_SUCCESS ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_Release (TYPE_5__*) ; 
 scalar_t__ date_Get (int /*<<< orphan*/ *) ; 
 scalar_t__ date_Increment (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_5__* decoder_NewAudioBuffer (TYPE_3__*,unsigned int) ; 
 int /*<<< orphan*/  decoder_QueueAudio (TYPE_3__*,TYPE_5__*) ; 
 scalar_t__ decoder_UpdateAudioFormat (TYPE_3__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static int DecodeBlock( decoder_t *p_dec, block_t *p_block )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    if( p_block == NULL ) /* No Drain */
        return VLCDEC_SUCCESS;

    if( p_block->i_flags & (BLOCK_FLAG_CORRUPTED|BLOCK_FLAG_DISCONTINUITY) )
    {
        Flush( p_dec );
        if( p_block->i_flags & BLOCK_FLAG_CORRUPTED )
            goto skip;
    }

    if( p_block->i_pts != VLC_TICK_INVALID &&
        p_block->i_pts != date_Get( &p_sys->end_date ) )
    {
        date_Set( &p_sys->end_date, p_block->i_pts );
    }
    else if( date_Get( &p_sys->end_date ) == VLC_TICK_INVALID )
        /* We've just started the stream, wait for the first PTS. */
        goto skip;

    unsigned samples = (8 * p_block->i_buffer) / p_sys->framebits;
    if( samples == 0 )
        goto skip;

    if( p_sys->decode != NULL )
    {
        if( decoder_UpdateAudioFormat( p_dec ) )
            goto skip;
        block_t *p_out = decoder_NewAudioBuffer( p_dec, samples );
        if( p_out == NULL )
            goto skip;

        p_sys->decode( p_out->p_buffer, p_block->p_buffer,
                       samples * p_dec->fmt_in.audio.i_channels );
        block_Release( p_block );
        p_block = p_out;
    }
    else
    {
        if( decoder_UpdateAudioFormat( p_dec ) )
            goto skip;
        p_block->i_nb_samples = samples;
        p_block->i_buffer = samples * (p_sys->framebits / 8);
    }

    p_block->i_pts = date_Get( &p_sys->end_date );
    p_block->i_length = date_Increment( &p_sys->end_date, samples )
                      - p_block->i_pts;
    decoder_QueueAudio( p_dec, p_block );
    return VLCDEC_SUCCESS;
skip:
    block_Release( p_block );
    return VLCDEC_SUCCESS;
}