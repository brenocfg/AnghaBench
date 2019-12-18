#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_18__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ decoder_t ;
struct TYPE_19__ {scalar_t__ i_block; int codec; int /*<<< orphan*/  i_samplesperblock; int /*<<< orphan*/  end_date; } ;
typedef  TYPE_2__ decoder_sys_t ;
struct TYPE_20__ {int i_flags; scalar_t__ i_pts; scalar_t__ i_buffer; scalar_t__ i_length; scalar_t__ p_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
#define  ADPCM_DK3 133 
#define  ADPCM_DK4 132 
#define  ADPCM_EA 131 
#define  ADPCM_IMA_QT 130 
#define  ADPCM_IMA_WAV 129 
#define  ADPCM_MS 128 
 int BLOCK_FLAG_CORRUPTED ; 
 int BLOCK_FLAG_DISCONTINUITY ; 
 int /*<<< orphan*/  DecodeAdpcmDk3 (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  DecodeAdpcmDk4 (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  DecodeAdpcmEA (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  DecodeAdpcmImaQT (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  DecodeAdpcmImaWav (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  DecodeAdpcmMs (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  Flush (TYPE_1__*) ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  block_Release (TYPE_3__*) ; 
 scalar_t__ date_Get (int /*<<< orphan*/ *) ; 
 scalar_t__ date_Increment (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_3__* decoder_NewAudioBuffer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ decoder_UpdateAudioFormat (TYPE_1__*) ; 

__attribute__((used)) static block_t *DecodeBlock( decoder_t *p_dec, block_t **pp_block )
{
    decoder_sys_t *p_sys  = p_dec->p_sys;
    block_t *p_block;

    if( !*pp_block ) return NULL;

    p_block = *pp_block;

    if( p_block->i_flags & (BLOCK_FLAG_DISCONTINUITY|BLOCK_FLAG_CORRUPTED) )
    {
        Flush( p_dec );
        if( p_block->i_flags & BLOCK_FLAG_CORRUPTED )
            goto drop;
    }

    if( p_block->i_pts != VLC_TICK_INVALID &&
        p_block->i_pts != date_Get( &p_sys->end_date ) )
    {
        date_Set( &p_sys->end_date, p_block->i_pts );
    }
    else if( date_Get( &p_sys->end_date ) == VLC_TICK_INVALID )
        /* We've just started the stream, wait for the first PTS. */
        goto drop;

    /* Don't re-use the same pts twice */
    p_block->i_pts = VLC_TICK_INVALID;

    if( p_block->i_buffer >= p_sys->i_block )
    {
        block_t *p_out;

        if( decoder_UpdateAudioFormat( p_dec ) )
            goto drop;
        p_out = decoder_NewAudioBuffer( p_dec, p_sys->i_samplesperblock );
        if( p_out == NULL )
            goto drop;

        p_out->i_pts = date_Get( &p_sys->end_date );
        p_out->i_length = date_Increment( &p_sys->end_date,
                                     p_sys->i_samplesperblock ) - p_out->i_pts;

        switch( p_sys->codec )
        {
        case ADPCM_IMA_QT:
            DecodeAdpcmImaQT( p_dec, (int16_t*)p_out->p_buffer,
                              p_block->p_buffer );
            break;
        case ADPCM_IMA_WAV:
            DecodeAdpcmImaWav( p_dec, (int16_t*)p_out->p_buffer,
                               p_block->p_buffer );
            break;
        case ADPCM_MS:
            DecodeAdpcmMs( p_dec, (int16_t*)p_out->p_buffer,
                           p_block->p_buffer );
            break;
        case ADPCM_DK4:
            DecodeAdpcmDk4( p_dec, (int16_t*)p_out->p_buffer,
                            p_block->p_buffer );
            break;
        case ADPCM_DK3:
            DecodeAdpcmDk3( p_dec, (int16_t*)p_out->p_buffer,
                            p_block->p_buffer );
            break;
        case ADPCM_EA:
            DecodeAdpcmEA( p_dec, (int16_t*)p_out->p_buffer,
                           p_block->p_buffer );
        default:
            break;
        }

        p_block->p_buffer += p_sys->i_block;
        p_block->i_buffer -= p_sys->i_block;
        return p_out;
    }

drop:
    block_Release( p_block );
    *pp_block = NULL;
    return NULL;
}