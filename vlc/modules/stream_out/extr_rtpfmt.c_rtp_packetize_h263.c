#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  sout_stream_id_sys_t ;
struct TYPE_7__ {int i_buffer; scalar_t__ i_pts; scalar_t__ i_dts; int i_length; scalar_t__* p_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int RTP_H263_HEADER_SIZE ; 
 int RTP_H263_PAYLOAD_START ; 
 int /*<<< orphan*/  SetWBE (scalar_t__*,int) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int __MIN (int,int) ; 
 TYPE_1__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,scalar_t__*,int) ; 
 int rtp_mtu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtp_packetize_common (int /*<<< orphan*/ *,TYPE_1__*,int,scalar_t__) ; 
 int /*<<< orphan*/  rtp_packetize_send (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int rtp_packetize_h263( sout_stream_id_sys_t *id, block_t *in )
{
    uint8_t *p_data = in->p_buffer;
    int     i_data  = in->i_buffer;
    int     i;
    int     i_max   = rtp_mtu (id) - RTP_H263_HEADER_SIZE; /* payload max in one packet */
    int     i_count;
    int     b_p_bit;
    int     b_v_bit = 0; // no pesky error resilience
    int     i_plen = 0; // normally plen=0 for PSC packet
    int     i_pebit = 0; // because plen=0
    uint16_t h;

    if( i_data < 2 )
    {
        block_Release(in);
        return VLC_EGENERIC;
    }
    if( p_data[0] || p_data[1] )
    {
        block_Release(in);
        return VLC_EGENERIC;
    }
    /* remove 2 leading 0 bytes */
    p_data += 2;
    i_data -= 2;
    i_count = ( i_data + i_max - 1 ) / i_max;

    for( i = 0; i < i_count; i++ )
    {
        int      i_payload = __MIN( i_max, i_data );
        block_t *out = block_Alloc( RTP_H263_PAYLOAD_START + i_payload );
        b_p_bit = (i == 0) ? 1 : 0;
        h = ( b_p_bit << 10 )|
            ( b_v_bit << 9  )|
            ( i_plen  << 3  )|
              i_pebit;

        /* rtp common header */
        //b_m_bit = 1; // always contains end of frame
        rtp_packetize_common( id, out, (i == i_count - 1)?1:0,
                          in->i_pts != VLC_TICK_INVALID ? in->i_pts : in->i_dts );

        /* h263 header */
        SetWBE( out->p_buffer + 12, h );
        memcpy( &out->p_buffer[RTP_H263_PAYLOAD_START], p_data, i_payload );

        out->i_dts    = in->i_dts + i * in->i_length / i_count;
        out->i_length = in->i_length / i_count;

        rtp_packetize_send( id, out );

        p_data += i_payload;
        i_data -= i_payload;
    }

    block_Release(in);
    return VLC_SUCCESS;
}