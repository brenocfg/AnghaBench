#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int /*<<< orphan*/  bytes; scalar_t__ packet; } ;
typedef  TYPE_2__ ogg_packet ;
typedef  int /*<<< orphan*/  int16_t ;
struct TYPE_15__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ decoder_t ;
struct TYPE_16__ {scalar_t__ i_frame_in_packet; TYPE_1__* p_header; int /*<<< orphan*/  end_date; int /*<<< orphan*/  stereo; int /*<<< orphan*/  bits; int /*<<< orphan*/  p_state; } ;
typedef  TYPE_4__ decoder_sys_t ;
struct TYPE_17__ {scalar_t__ i_pts; scalar_t__ i_length; scalar_t__ p_buffer; } ;
typedef  TYPE_5__ block_t ;
struct TYPE_13__ {scalar_t__ frames_per_packet; int nb_channels; int /*<<< orphan*/  frame_size; } ;

/* Variables and functions */
 scalar_t__ date_Get (int /*<<< orphan*/ *) ; 
 scalar_t__ date_Increment (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 TYPE_5__* decoder_NewAudioBuffer (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ decoder_UpdateAudioFormat (TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  speex_bits_read_from (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ speex_bits_remaining (int /*<<< orphan*/ *) ; 
 int speex_decode_int (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  speex_decode_stereo_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static block_t *DecodePacket( decoder_t *p_dec, ogg_packet *p_oggpacket )
{
    decoder_sys_t *p_sys = p_dec->p_sys;

    if( p_oggpacket->bytes )
    {
        /* Copy Ogg packet to Speex bitstream */
        speex_bits_read_from( &p_sys->bits, (char *)p_oggpacket->packet,
                              p_oggpacket->bytes );
        p_sys->i_frame_in_packet = 0;
    }

    /* Decode one frame at a time */
    if( p_sys->i_frame_in_packet < p_sys->p_header->frames_per_packet )
    {
        block_t *p_aout_buffer;
        if( p_sys->p_header->frame_size == 0 )
            return NULL;

        if( decoder_UpdateAudioFormat( p_dec ) )
            return NULL;
        p_aout_buffer =
            decoder_NewAudioBuffer( p_dec, p_sys->p_header->frame_size );
        if( !p_aout_buffer )
        {
            return NULL;
        }

        switch( speex_decode_int( p_sys->p_state, &p_sys->bits,
                                  (int16_t *)p_aout_buffer->p_buffer ) )
        {
            case -2:
                msg_Err( p_dec, "decoding error: corrupted stream?" );
                /* fall through */
            case -1: /* End of stream */
                return NULL;
        }

        if( speex_bits_remaining( &p_sys->bits ) < 0 )
        {
            msg_Err( p_dec, "decoding overflow: corrupted stream?" );
        }

        if( p_sys->p_header->nb_channels == 2 )
            speex_decode_stereo_int( (int16_t *)p_aout_buffer->p_buffer,
                                     p_sys->p_header->frame_size,
                                     &p_sys->stereo );

        /* Date management */
        p_aout_buffer->i_pts = date_Get( &p_sys->end_date );
        p_aout_buffer->i_length =
            date_Increment( &p_sys->end_date, p_sys->p_header->frame_size )
            - p_aout_buffer->i_pts;

        p_sys->i_frame_in_packet++;

        return p_aout_buffer;
    }
    else
    {
        return NULL;
    }
}