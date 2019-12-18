#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_34__   TYPE_6__ ;
typedef  struct TYPE_33__   TYPE_5__ ;
typedef  struct TYPE_32__   TYPE_4__ ;
typedef  struct TYPE_31__   TYPE_3__ ;
typedef  struct TYPE_30__   TYPE_2__ ;
typedef  struct TYPE_29__   TYPE_1__ ;
typedef  struct TYPE_28__   TYPE_10__ ;

/* Type definitions */
struct TYPE_31__ {int i_frame_size; int i_substream_header_size; int /*<<< orphan*/  syncword; int /*<<< orphan*/  i_frame_length; int /*<<< orphan*/  i_rate; } ;
typedef  TYPE_3__ vlc_dts_header_t ;
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_30__ {void* i_profile; } ;
struct TYPE_32__ {TYPE_2__ fmt_out; TYPE_5__* p_sys; } ;
typedef  TYPE_4__ decoder_t ;
struct TYPE_28__ {TYPE_1__* p_block; } ;
struct TYPE_33__ {int i_state; scalar_t__ i_pts; int i_input_size; int i_next_offset; int b_discontinuity; TYPE_10__ bytestream; TYPE_3__ second; TYPE_3__ first; int /*<<< orphan*/  end_date; } ;
typedef  TYPE_5__ decoder_sys_t ;
struct TYPE_34__ {int i_flags; scalar_t__ i_pts; int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_6__ block_t ;
struct TYPE_29__ {scalar_t__ i_pts; } ;

/* Variables and functions */
 int BLOCK_FLAG_CORRUPTED ; 
 int BLOCK_FLAG_DISCONTINUITY ; 
 int /*<<< orphan*/  DTS_SYNC_SUBSTREAM ; 
 int /*<<< orphan*/  DTS_SYNC_SUBSTREAM_LBR ; 
 TYPE_6__* GetOutBuffer (TYPE_4__*) ; 
 void* PROFILE_DTS ; 
 void* PROFILE_DTS_EXPRESS ; 
 void* PROFILE_DTS_HD ; 
 int /*<<< orphan*/  PacketizeFlush (TYPE_4__*) ; 
#define  STATE_GET_DATA 135 
#define  STATE_HEADER 134 
#define  STATE_NEXT_SYNC 133 
#define  STATE_NEXT_SYNC_SUBSTREAM_EXTENSIONS 132 
#define  STATE_NOSYNC 131 
#define  STATE_SEND_DATA 130 
#define  STATE_SYNC 129 
#define  STATE_SYNC_SUBSTREAM_EXTENSIONS 128 
 int VLC_DTS_HEADER_SIZE ; 
 int /*<<< orphan*/  VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  block_BytestreamFlush (TYPE_10__*) ; 
 TYPE_6__* block_BytestreamPop (TYPE_10__*) ; 
 int /*<<< orphan*/  block_BytestreamPush (TYPE_10__*,TYPE_6__*) ; 
 int /*<<< orphan*/  block_GetBytes (TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_PeekBytes (TYPE_10__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  block_PeekOffsetBytes (TYPE_10__*,int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  block_Release (TYPE_6__*) ; 
 int /*<<< orphan*/  block_SkipByte (TYPE_10__*) ; 
 int /*<<< orphan*/  block_SkipBytes (TYPE_10__*,int) ; 
 int /*<<< orphan*/  block_WaitBytes (TYPE_10__*,int) ; 
 scalar_t__ date_Get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  date_Set (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  vlc_dts_header_IsSync (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_dts_header_Parse (TYPE_3__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static block_t *PacketizeBlock( decoder_t *p_dec, block_t **pp_block )
{
    decoder_sys_t *p_sys = p_dec->p_sys;
    uint8_t p_header[VLC_DTS_HEADER_SIZE];
    block_t *p_out_buffer;

    block_t *p_block = pp_block ? *pp_block : NULL;

    if( p_block )
    {
        if ( p_block->i_flags & (BLOCK_FLAG_DISCONTINUITY|BLOCK_FLAG_CORRUPTED) ) {
            /* First always drain complete blocks before discontinuity */
            block_t *p_drain = PacketizeBlock( p_dec, NULL );
            if(p_drain)
                return p_drain;

            PacketizeFlush( p_dec );

            if ( p_block->i_flags & BLOCK_FLAG_CORRUPTED ) {
                block_Release( p_block );
                return NULL;
            }
        }

        if ( p_block->i_pts == VLC_TICK_INVALID &&
             date_Get( &p_sys->end_date ) == VLC_TICK_INVALID ) {
            /* We've just started the stream, wait for the first PTS. */
            block_Release( p_block );
            return NULL;
        }

        block_BytestreamPush( &p_sys->bytestream, p_block );
    }

    while( 1 )
    {
        switch( p_sys->i_state )
        {
        case STATE_NOSYNC:
            while( block_PeekBytes( &p_sys->bytestream, p_header, 6 )
                   == VLC_SUCCESS )
            {
                if( vlc_dts_header_IsSync( p_header, 6 ) )
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
            /* Get DTS frame header (VLC_DTS_HEADER_SIZE bytes) */
            if( block_PeekBytes( &p_sys->bytestream, p_header,
                                 VLC_DTS_HEADER_SIZE ) != VLC_SUCCESS )
            {
                /* Need more data */
                return NULL;
            }

            /* Check if frame is valid and get frame info */
            if( vlc_dts_header_Parse( &p_sys->first, p_header,
                                      VLC_DTS_HEADER_SIZE ) != VLC_SUCCESS )
            {
                msg_Dbg( p_dec, "emulated sync word" );
                block_SkipByte( &p_sys->bytestream );
                p_sys->i_state = STATE_NOSYNC;
                break;
            }

            if( p_sys->first.syncword == DTS_SYNC_SUBSTREAM )
                p_sys->i_state = STATE_SYNC_SUBSTREAM_EXTENSIONS;
            else
                p_sys->i_state = STATE_NEXT_SYNC;
            p_sys->i_input_size = p_sys->i_next_offset = p_sys->first.i_frame_size;
            break;

        case STATE_SYNC_SUBSTREAM_EXTENSIONS:
            /* Peek into the substream extension (sync + header size < frame_size) */
            if( block_PeekOffsetBytes( &p_sys->bytestream,
                                       p_sys->first.i_substream_header_size,
                                       p_header,
                                       VLC_DTS_HEADER_SIZE ) != VLC_SUCCESS )
            {
                /* Need more data */
                return NULL;
            }

            vlc_dts_header_t xssheader;
            if( vlc_dts_header_Parse( &xssheader, p_header,
                                      VLC_DTS_HEADER_SIZE ) != VLC_SUCCESS )
            {
                msg_Dbg( p_dec, "emulated substream sync word, can't find extension" );
                block_SkipByte( &p_sys->bytestream );
                p_sys->i_state = STATE_NOSYNC;
                break;
            }

            if( xssheader.syncword == DTS_SYNC_SUBSTREAM_LBR )
            {
                /*
                 * LBR exists as independant SUBSTREAM. It is seen valid
                 * only when SUBSTREAM[LBR]..SUBTREAM.
                 * CORE...SUBSTREAM is regular extension.
                 * SUBSTREAM...CORE is sync issue.
                 */
                p_dec->fmt_out.i_profile = PROFILE_DTS_EXPRESS;
                p_sys->first.i_rate = xssheader.i_rate;
                p_sys->first.i_frame_length = xssheader.i_frame_length;
                p_sys->i_state = STATE_NEXT_SYNC;
                break;
            }

            msg_Warn( p_dec, "substream without the paired core stream, skip it" );
            p_sys->i_state = STATE_NOSYNC;
            p_dec->fmt_out.i_profile = PROFILE_DTS;
            if( block_SkipBytes( &p_sys->bytestream,
                                 p_sys->first.i_frame_size ) != VLC_SUCCESS )
                return NULL;
            break;

        case STATE_NEXT_SYNC:
            /* Check if next expected frame contains the sync word */
            while( p_sys->i_state == STATE_NEXT_SYNC )
            {
                if( block_PeekOffsetBytes( &p_sys->bytestream,
                                           p_sys->i_next_offset, p_header,
                                           VLC_DTS_HEADER_SIZE )
                                           != VLC_SUCCESS )
                {
                    if( p_block == NULL ) /* drain */
                    {
                        p_sys->i_state = STATE_GET_DATA;
                        break;
                    }
                    /* Need more data */
                    return NULL;
                }

                if( p_header[0] == 0 )
                {
                    /* DTS wav files, audio CD's and some mkvs use stuffing */
                    p_sys->i_next_offset++;
                    continue;
                }

                if( !vlc_dts_header_IsSync( p_header, VLC_DTS_HEADER_SIZE ) )
                {
                    /* Even frame size is likely incorrect FSIZE #18166 */
                    if( (p_sys->first.i_frame_size % 2) && p_sys->i_next_offset > 0 &&
                        block_PeekOffsetBytes( &p_sys->bytestream,
                                               p_sys->i_next_offset - 1, p_header,
                                               VLC_DTS_HEADER_SIZE ) == 0 &&
                         vlc_dts_header_IsSync( p_header, VLC_DTS_HEADER_SIZE ) )
                    {
                        p_sys->i_input_size = p_sys->i_next_offset = p_sys->first.i_frame_size - 1;
                        /* reenter */
                        break;
                    }
                    msg_Dbg( p_dec, "emulated sync word "
                             "(no sync on following frame)" );
                    p_sys->i_state = STATE_NOSYNC;
                    block_SkipByte( &p_sys->bytestream );
                    break;
                }

                /* Check if a DTS substream packet is located just after
                 * the core packet */
                if( p_sys->i_next_offset == p_sys->first.i_frame_size &&
                    vlc_dts_header_Parse( &p_sys->second,
                                          p_header, VLC_DTS_HEADER_SIZE ) == VLC_SUCCESS &&
                    p_sys->second.syncword == DTS_SYNC_SUBSTREAM )
                {
                    p_sys->i_state = STATE_NEXT_SYNC_SUBSTREAM_EXTENSIONS;
                }
                else
                {
                    p_dec->fmt_out.i_profile = PROFILE_DTS;
                    p_sys->i_state = STATE_GET_DATA;
                }
            }
            break;

        case STATE_NEXT_SYNC_SUBSTREAM_EXTENSIONS:
            assert(p_sys->second.syncword == DTS_SYNC_SUBSTREAM);
            if( p_sys->first.syncword == DTS_SYNC_SUBSTREAM )
            {
                /* First substream must have been LBR */
                p_dec->fmt_out.i_profile = PROFILE_DTS_EXPRESS;
            }
            else /* Otherwise that's core + extensions, we need to output both */
            {
                p_dec->fmt_out.i_profile = PROFILE_DTS_HD;
                p_sys->i_input_size += p_sys->second.i_frame_size;
            }
            p_sys->i_state = STATE_GET_DATA;
            break;

        case STATE_GET_DATA:
            /* Make sure we have enough data. */
            if( block_WaitBytes( &p_sys->bytestream,
                                 p_sys->i_input_size ) != VLC_SUCCESS )
            {
                /* Need more data */
                return NULL;
            }
            p_sys->i_state = STATE_SEND_DATA;
            /* fallthrough */

        case STATE_SEND_DATA:
            if( !(p_out_buffer = GetOutBuffer( p_dec )) )
            {
                return NULL;
            }

            /* Copy the whole frame into the buffer. When we reach this point
             * we already know we have enough data available. */
            block_GetBytes( &p_sys->bytestream, p_out_buffer->p_buffer,
                            p_out_buffer->i_buffer );

            /* Make sure we don't reuse the same pts twice */
            if( p_sys->i_pts == p_sys->bytestream.p_block->i_pts )
                p_sys->i_pts = p_sys->bytestream.p_block->i_pts = VLC_TICK_INVALID;

            if( p_sys->b_discontinuity )
            {
                p_sys->b_discontinuity = false;
                p_out_buffer->i_flags |= BLOCK_FLAG_DISCONTINUITY;
            }

            /* So p_block doesn't get re-added several times */
            if( pp_block )
                *pp_block = block_BytestreamPop( &p_sys->bytestream );

            p_sys->i_state = STATE_NOSYNC;

            return p_out_buffer;
        }
    }
}