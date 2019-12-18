#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_1__ ;
typedef  struct TYPE_26__   TYPE_12__ ;

/* Type definitions */
struct TYPE_26__ {unsigned int i_rate; unsigned int i_channels; unsigned int i_physical_channels; int i_bitspersample; int /*<<< orphan*/  i_format; } ;
struct TYPE_27__ {int /*<<< orphan*/  i_codec; TYPE_12__ audio; } ;
struct TYPE_28__ {TYPE_1__ fmt_out; TYPE_3__* p_sys; } ;
typedef  TYPE_2__ decoder_t ;
struct TYPE_29__ {scalar_t__ i_header_size; int i_type; int /*<<< orphan*/  pi_chan_table; int /*<<< orphan*/  i_chans_to_reorder; int /*<<< orphan*/  end_date; scalar_t__ b_packetizer; } ;
typedef  TYPE_3__ decoder_sys_t ;
struct TYPE_30__ {int i_flags; scalar_t__ i_pts; scalar_t__ i_buffer; scalar_t__ i_dts; int /*<<< orphan*/  p_buffer; void* i_length; } ;
typedef  TYPE_4__ block_t ;
struct TYPE_31__ {int i_bits; int i_channels; } ;
typedef  TYPE_5__ aob_group_t ;

/* Variables and functions */
 int /*<<< orphan*/  AobExtract (TYPE_4__*,TYPE_4__*,unsigned int,TYPE_5__*) ; 
 int AobHeader (unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int BLOCK_FLAG_CORRUPTED ; 
 int BLOCK_FLAG_DISCONTINUITY ; 
 int /*<<< orphan*/  BdExtract (TYPE_4__*,TYPE_4__*,int,unsigned int,unsigned int,unsigned int) ; 
 int BdHeader (TYPE_3__*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Flush (TYPE_2__*) ; 
#define  LPCM_AOB 131 
#define  LPCM_BD 130 
#define  LPCM_VOB 129 
#define  LPCM_WIDI 128 
 int /*<<< orphan*/  VLC_CODEC_S16N ; 
 int /*<<< orphan*/  VLC_CODEC_S32N ; 
 scalar_t__ VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  VobExtract (TYPE_4__*,TYPE_4__*,unsigned int) ; 
 int VobHeader (unsigned int*,unsigned int*,unsigned int*,unsigned int*,int /*<<< orphan*/ ) ; 
 int WidiHeader (unsigned int*,unsigned int*,unsigned int*,unsigned int*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  aout_ChannelReorder (int /*<<< orphan*/ ,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  aout_FormatPrepare (TYPE_12__*) ; 
 int /*<<< orphan*/  block_Release (TYPE_4__*) ; 
 scalar_t__ date_Get (int /*<<< orphan*/ *) ; 
 void* date_Increment (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  date_Init (int /*<<< orphan*/ *,unsigned int,int) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,scalar_t__) ; 
 TYPE_4__* decoder_NewAudioBuffer (TYPE_2__*,int) ; 
 scalar_t__ decoder_UpdateAudioFormat (TYPE_2__*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 

__attribute__((used)) static block_t *Packetize( decoder_t *p_dec, block_t **pp_block )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    block_t       *p_block;
    unsigned int  i_rate = 0, i_original_channels = 0, i_channels = 0, i_bits = 0;
    int           i_frame_length;

    if( !pp_block || !*pp_block ) return NULL;

    p_block = *pp_block;
    *pp_block = NULL; /* So the packet doesn't get re-sent */

    if( p_block->i_flags & (BLOCK_FLAG_CORRUPTED|BLOCK_FLAG_DISCONTINUITY) )
    {
        Flush( p_dec );
        if( p_block->i_flags & BLOCK_FLAG_CORRUPTED )
        {
            block_Release( p_block );
            *pp_block = NULL;
            return NULL;
        }
    }

    /* Date management */
    if( p_block->i_pts != VLC_TICK_INVALID &&
        p_block->i_pts != date_Get( &p_sys->end_date ) )
    {
        date_Set( &p_sys->end_date, p_block->i_pts );
    }

    if( date_Get( &p_sys->end_date ) == VLC_TICK_INVALID )
    {
        /* We've just started the stream, wait for the first PTS. */
        block_Release( p_block );
        return NULL;
    }

    if( p_block->i_buffer <= p_sys->i_header_size )
    {
        msg_Err(p_dec, "frame is too short");
        block_Release( p_block );
        return NULL;
    }

    int i_ret;
    unsigned i_channels_padding = 0;
    unsigned i_padding = 0; /* only for AOB */
    aob_group_t p_aob_group[2];

    switch( p_sys->i_type )
    {
    case LPCM_VOB:
        i_ret = VobHeader( &i_rate, &i_channels, &i_original_channels, &i_bits,
                           p_block->p_buffer );
        break;
    case LPCM_AOB:
        i_ret = AobHeader( &i_rate, &i_channels, &i_original_channels, &i_bits, &i_padding,
                           p_aob_group,
                           p_block->p_buffer );
        break;
    case LPCM_BD:
        i_ret = BdHeader( p_sys, &i_rate, &i_channels, &i_channels_padding, &i_original_channels, &i_bits,
                          p_block->p_buffer );
        break;
    case LPCM_WIDI:
        i_ret = WidiHeader( &i_rate, &i_channels, &i_original_channels, &i_bits,
                            p_block->p_buffer );
        break;
    default:
        abort();
    }

    if( i_ret || p_block->i_buffer <= p_sys->i_header_size + i_padding )
    {
        msg_Warn( p_dec, "no frame sync or too small frame" );
        block_Release( p_block );
        return NULL;
    }

    /* Set output properties */
    if( p_dec->fmt_out.audio.i_rate != i_rate )
    {
        date_Init( &p_sys->end_date, i_rate, 1 );
        date_Set( &p_sys->end_date, p_block->i_pts );
    }
    p_dec->fmt_out.audio.i_rate = i_rate;
    p_dec->fmt_out.audio.i_channels = i_channels;
    p_dec->fmt_out.audio.i_physical_channels = i_original_channels;

    if ( p_sys->i_type == LPCM_AOB )
    {
        i_frame_length = (p_block->i_buffer - p_sys->i_header_size - i_padding) /
                         (
                            ( (p_aob_group[0].i_bits / 8) * p_aob_group[0].i_channels ) +
                            ( (p_aob_group[1].i_bits / 8) * p_aob_group[1].i_channels )
                         );
    }
    else
    {
        i_frame_length = (p_block->i_buffer - p_sys->i_header_size - i_padding) /
                         (i_channels + i_channels_padding) * 8 / i_bits;
    }

    if( p_sys->b_packetizer )
    {
        p_block->i_pts = p_block->i_dts = date_Get( &p_sys->end_date );
        p_block->i_length =
            date_Increment( &p_sys->end_date, i_frame_length ) -
            p_block->i_pts;

        /* Just pass on the incoming frame */
        return p_block;
    }
    else
    {
        /* */
        if( i_bits == 16 )
        {
            p_dec->fmt_out.audio.i_format =
            p_dec->fmt_out.i_codec = VLC_CODEC_S16N;
            p_dec->fmt_out.audio.i_bitspersample = 16;
        }
        else
        {
            p_dec->fmt_out.audio.i_format =
            p_dec->fmt_out.i_codec = VLC_CODEC_S32N;
            p_dec->fmt_out.audio.i_bitspersample = 32;
        }
        aout_FormatPrepare(&p_dec->fmt_out.audio);

        /* */
        block_t *p_aout_buffer;
        if( decoder_UpdateAudioFormat( p_dec ) != VLC_SUCCESS ||
           !(p_aout_buffer = decoder_NewAudioBuffer( p_dec, i_frame_length )) )
        {
            block_Release( p_block );
            return NULL;
        }

        p_aout_buffer->i_pts = date_Get( &p_sys->end_date );
        p_aout_buffer->i_length =
            date_Increment( &p_sys->end_date, i_frame_length )
            - p_aout_buffer->i_pts;

        p_block->p_buffer += p_sys->i_header_size + i_padding;
        p_block->i_buffer -= p_sys->i_header_size + i_padding;

        switch( p_sys->i_type )
        {
        case LPCM_WIDI:
        case LPCM_VOB:
            VobExtract( p_aout_buffer, p_block, i_bits );
            break;
        case LPCM_AOB:
            AobExtract( p_aout_buffer, p_block, i_bits, p_aob_group );
            break;
        default:
            vlc_assert_unreachable();
        case LPCM_BD:
            BdExtract( p_aout_buffer, p_block, i_frame_length, i_channels, i_channels_padding, i_bits );
            break;
        }

        if( p_sys->i_chans_to_reorder )
        {
            aout_ChannelReorder( p_aout_buffer->p_buffer, p_aout_buffer->i_buffer,
                                 p_sys->i_chans_to_reorder, p_sys->pi_chan_table,
                                 p_dec->fmt_out.i_codec );
        }

        block_Release( p_block );
        return p_aout_buffer;
    }
}