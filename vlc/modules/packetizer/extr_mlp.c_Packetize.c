#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_7__ ;
typedef  struct TYPE_33__   TYPE_6__ ;
typedef  struct TYPE_32__   TYPE_5__ ;
typedef  struct TYPE_31__   TYPE_4__ ;
typedef  struct TYPE_30__   TYPE_3__ ;
typedef  struct TYPE_29__   TYPE_2__ ;
typedef  struct TYPE_28__   TYPE_1__ ;
typedef  struct TYPE_27__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_31__ {int /*<<< orphan*/  i_samples; int /*<<< orphan*/  i_channels_conf; int /*<<< orphan*/  i_channels; int /*<<< orphan*/  i_rate; } ;
typedef  TYPE_4__ mlp_header_t ;
struct TYPE_28__ {int /*<<< orphan*/  i_frame_length; int /*<<< orphan*/  i_bytes_per_frame; int /*<<< orphan*/  i_physical_channels; int /*<<< orphan*/  i_channels; int /*<<< orphan*/  i_rate; } ;
struct TYPE_29__ {TYPE_1__ audio; } ;
struct TYPE_32__ {TYPE_2__ fmt_out; TYPE_6__* p_sys; } ;
typedef  TYPE_5__ decoder_t ;
struct TYPE_27__ {TYPE_3__* p_block; } ;
struct TYPE_33__ {int i_state; int b_mlp; scalar_t__ i_pts; int b_discontinuity; TYPE_10__ bytestream; TYPE_4__ mlp; int /*<<< orphan*/  end_date; int /*<<< orphan*/  i_frame_size; } ;
typedef  TYPE_6__ decoder_sys_t ;
struct TYPE_34__ {int i_flags; scalar_t__ i_pts; scalar_t__ i_dts; scalar_t__ i_length; int /*<<< orphan*/  i_nb_samples; int /*<<< orphan*/ * p_buffer; int /*<<< orphan*/  i_buffer; } ;
typedef  TYPE_7__ block_t ;
struct TYPE_30__ {scalar_t__ i_pts; } ;

/* Variables and functions */
 int BLOCK_FLAG_CORRUPTED ; 
 int BLOCK_FLAG_DISCONTINUITY ; 
 int /*<<< orphan*/  Flush (TYPE_5__*) ; 
 int MLP_HEADER_SIZE ; 
#define  STATE_GET_DATA 133 
#define  STATE_HEADER 132 
#define  STATE_NEXT_SYNC 131 
#define  STATE_NOSYNC 130 
#define  STATE_SEND_DATA 129 
#define  STATE_SYNC 128 
 int /*<<< orphan*/  SyncInfo (int /*<<< orphan*/ *,int*,TYPE_4__*) ; 
 int /*<<< orphan*/  SyncInfoDolby (int /*<<< orphan*/ *) ; 
 scalar_t__ VLC_TICK_INVALID ; 
 TYPE_7__* block_Alloc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_BytestreamFlush (TYPE_10__*) ; 
 TYPE_7__* block_BytestreamPop (TYPE_10__*) ; 
 int /*<<< orphan*/  block_BytestreamPush (TYPE_10__*,TYPE_7__*) ; 
 int /*<<< orphan*/  block_GetBytes (TYPE_10__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_PeekBytes (TYPE_10__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  block_PeekOffsetBytes (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  block_Release (TYPE_7__*) ; 
 int /*<<< orphan*/  block_SkipByte (TYPE_10__*) ; 
 int /*<<< orphan*/  block_WaitBytes (TYPE_10__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  date_Change (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 scalar_t__ date_Get (int /*<<< orphan*/ *) ; 
 scalar_t__ date_Increment (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_5__*,char*) ; 
 int /*<<< orphan*/  msg_Info (TYPE_5__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static block_t *Packetize( decoder_t *p_dec, block_t **pp_block )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    uint8_t p_header[MLP_HEADER_SIZE];
    block_t *p_out_buffer;

    block_t *p_block = pp_block ? *pp_block : NULL;

    if ( p_block )
    {
        if( p_block->i_flags & (BLOCK_FLAG_DISCONTINUITY|BLOCK_FLAG_CORRUPTED) )
        {
            /* First always drain complete blocks before discontinuity */
            block_t *p_drain = Packetize( p_dec, NULL );
            if( p_drain )
                return p_drain;

            Flush( p_dec );

            if( p_block->i_flags & BLOCK_FLAG_CORRUPTED )
            {
                block_Release( p_block );
                return NULL;
            }
        }

        if( p_block->i_pts == VLC_TICK_INVALID &&
            date_Get( &p_sys->end_date ) == VLC_TICK_INVALID )
        {
            /* We've just started the stream, wait for the first PTS. */
            msg_Dbg( p_dec, "waiting for PTS" );
            block_Release( p_block );
            return NULL;
        }

        block_BytestreamPush( &p_sys->bytestream, p_block );
    }

    for( ;; )
    {
        switch( p_sys->i_state )
        {
        case STATE_NOSYNC:
            while( !block_PeekBytes( &p_sys->bytestream, p_header, MLP_HEADER_SIZE ) )
            {
                if( SyncInfo( p_header, &p_sys->b_mlp, &p_sys->mlp ) > 0 )
                {
                    p_sys->i_state = STATE_SYNC;
                    break;
                }
                else if( SyncInfoDolby( p_header ) > 0 )
                {
                    p_sys->i_state = STATE_SYNC;
                    break;
                }
                block_SkipByte( &p_sys->bytestream );
            }
            if( p_sys->i_state != STATE_SYNC )
            {
                block_BytestreamFlush( &p_sys->bytestream );

                /* Need more data */
                return NULL;
            }
            /* fallthrough */

        case STATE_SYNC:
            /* New frame, set the Presentation Time Stamp */
            p_sys->i_pts = p_sys->bytestream.p_block->i_pts;
            if( p_sys->i_pts != VLC_TICK_INVALID &&
                p_sys->i_pts != date_Get( &p_sys->end_date ) )
            {
                date_Set( &p_sys->end_date, p_sys->i_pts );
            }
            p_sys->i_state = STATE_HEADER;
            /* fallthrough */

        case STATE_HEADER:
            /* Get a MLP header */
            if( block_PeekBytes( &p_sys->bytestream, p_header, MLP_HEADER_SIZE ) )
            {
                /* Need more data */
                return NULL;
            }

            /* Check if frame is valid and get frame info */
            p_sys->i_frame_size = SyncInfoDolby( p_header );
            if( p_sys->i_frame_size <= 0 )
                p_sys->i_frame_size = SyncInfo( p_header, &p_sys->b_mlp, &p_sys->mlp );
            if( p_sys->i_frame_size <= 0 )
            {
                msg_Dbg( p_dec, "emulated sync word" );
                block_SkipByte( &p_sys->bytestream );
                p_sys->b_mlp = false;
                p_sys->i_state = STATE_NOSYNC;
                break;
            }
            p_sys->i_state = STATE_NEXT_SYNC;
            /* fallthrough */

        case STATE_NEXT_SYNC:
            /* Check if next expected frame contains the sync word */
            if( block_PeekOffsetBytes( &p_sys->bytestream,
                                       p_sys->i_frame_size, p_header, MLP_HEADER_SIZE ) )
            {
                if( p_block == NULL ) /* drain */
                {
                    p_sys->i_state = STATE_GET_DATA;
                    break;
                }
                /* Need more data */
                return NULL;
            }

            bool b_mlp = p_sys->b_mlp;
            mlp_header_t mlp = p_sys->mlp;
            if( SyncInfo( p_header, &b_mlp, &mlp ) <= 0 && SyncInfoDolby( p_header ) <= 0 )
            {
                msg_Dbg( p_dec, "emulated sync word "
                         "(no sync on following frame)" );
                p_sys->b_mlp = false;
                p_sys->i_state = STATE_NOSYNC;
                block_SkipByte( &p_sys->bytestream );
                break;
            }
            p_sys->i_state = STATE_GET_DATA;
            break;

        case STATE_GET_DATA:
            /* Make sure we have enough data. */
            if( block_WaitBytes( &p_sys->bytestream, p_sys->i_frame_size ) )
            {
                /* Need more data */
                return NULL;
            }
            p_sys->i_state = STATE_SEND_DATA;
            /* fallthrough */

        case STATE_SEND_DATA:
            /* When we reach this point we already know we have enough
             * data available. */
            p_out_buffer = block_Alloc( p_sys->i_frame_size );
            if( !p_out_buffer )
                return NULL;

            /* Copy the whole frame into the buffer */
            block_GetBytes( &p_sys->bytestream,
                            p_out_buffer->p_buffer, p_out_buffer->i_buffer );

            /* Just ignore (E)AC3 frames */
            if( SyncInfoDolby( p_out_buffer->p_buffer ) > 0 )
            {
                block_Release( p_out_buffer );
                p_sys->i_state = STATE_NOSYNC;
                break;
            }

            /* Setup output */
            if( p_dec->fmt_out.audio.i_rate != p_sys->mlp.i_rate )
            {
                msg_Info( p_dec, "MLP channels: %d samplerate: %d",
                          p_sys->mlp.i_channels, p_sys->mlp.i_rate );

                if( p_sys->mlp.i_rate > 0 )
                    date_Change( &p_sys->end_date, p_sys->mlp.i_rate, 1 );
            }

            p_dec->fmt_out.audio.i_rate     = p_sys->mlp.i_rate;
            p_dec->fmt_out.audio.i_channels = p_sys->mlp.i_channels;
            p_dec->fmt_out.audio.i_physical_channels = p_sys->mlp.i_channels_conf;
            p_dec->fmt_out.audio.i_bytes_per_frame = p_sys->i_frame_size;
            p_dec->fmt_out.audio.i_frame_length = p_sys->mlp.i_samples;

            p_out_buffer->i_pts = p_out_buffer->i_dts = date_Get( &p_sys->end_date );
            p_out_buffer->i_nb_samples = p_sys->mlp.i_samples;

            p_out_buffer->i_length =
                date_Increment( &p_sys->end_date, p_sys->mlp.i_samples ) - p_out_buffer->i_pts;

            /* Make sure we don't reuse the same pts twice */
            if( p_sys->i_pts == p_sys->bytestream.p_block->i_pts )
                p_sys->i_pts = p_sys->bytestream.p_block->i_pts = VLC_TICK_INVALID;

            if( p_sys->b_discontinuity )
            {
                p_out_buffer->i_flags |= BLOCK_FLAG_DISCONTINUITY;
                p_sys->b_discontinuity = false;
            }

            /* So p_block doesn't get re-added several times */
            if( pp_block )
                *pp_block = block_BytestreamPop( &p_sys->bytestream );

            p_sys->i_state = STATE_NOSYNC;

            return p_out_buffer;
        }
    }

    return NULL;
}