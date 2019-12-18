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
typedef  int uint8_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  sout_stream_id_sys_t ;
typedef  int /*<<< orphan*/  hxxx_iterator_ctx_t ;
struct TYPE_7__ {int i_buffer; int* p_buffer; scalar_t__ i_pts; scalar_t__ i_dts; int i_length; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  SetDWBE (int*,int) ; 
 int VLC_SUCCESS ; 
 scalar_t__ VLC_TICK_INVALID ; 
 int __MIN (int,int) ; 
 TYPE_1__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 scalar_t__ hxxx_annexb_iterate_next (int /*<<< orphan*/ *,int const**,size_t*) ; 
 int /*<<< orphan*/  hxxx_iterator_init (int /*<<< orphan*/ *,int*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int rtp_mtu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtp_packetize_common (int /*<<< orphan*/ *,TYPE_1__*,int,scalar_t__) ; 
 int /*<<< orphan*/  rtp_packetize_send (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int rtp_packetize_mpv( sout_stream_id_sys_t *id, block_t *in )
{
    int     i_max   = rtp_mtu (id) - 4; /* payload max in one packet */
    int     i_count = ( in->i_buffer + i_max - 1 ) / i_max;

    uint8_t *p_data = in->p_buffer;
    int     i_data  = in->i_buffer;
    int     i;
    int     b_sequence_start = 0;
    int     i_temporal_ref = 0;
    int     i_picture_coding_type = 0;
    int     i_fbv = 0, i_bfc = 0, i_ffv = 0, i_ffc = 0;
    int     b_start_slice = 0;

    /* preparse this packet to get some info */
    hxxx_iterator_ctx_t it;
    hxxx_iterator_init( &it, in->p_buffer, in->i_buffer, 0 );
    const uint8_t *p_seq;
    size_t i_seq;
    while( hxxx_annexb_iterate_next( &it, &p_seq, &i_seq ) )
    {
        const uint8_t *p = p_seq;
        if( *p == 0xb3 )
        {
            /* sequence start code */
            b_sequence_start = 1;
        }
        else if( *p == 0x00 && i_seq >= 5 )
        {
            /* picture */
            i_temporal_ref = ( p[1] << 2) |((p[2]>>6)&0x03);
            i_picture_coding_type = (p[2] >> 3)&0x07;

            if( i_picture_coding_type == 2 ||
                i_picture_coding_type == 3 )
            {
                i_ffv = (p[3] >> 2)&0x01;
                i_ffc = ((p[3]&0x03) << 1)|((p[4]>>7)&0x01);
                if( i_seq > 5 && i_picture_coding_type == 3 )
                {
                    i_fbv = (p[4]>>6)&0x01;
                    i_bfc = (p[4]>>3)&0x07;
                }
            }
        }
        else if( *p <= 0xaf )
        {
            b_start_slice = 1;
        }
    }

    for( i = 0; i < i_count; i++ )
    {
        int           i_payload = __MIN( i_max, i_data );
        block_t *out = block_Alloc( 16 + i_payload );
        /* MBZ:5 T:1 TR:10 AN:1 N:1 S:1 B:1 E:1 P:3 FBV:1 BFC:3 FFV:1 FFC:3 */
        uint32_t      h = ( i_temporal_ref << 16 )|
                          ( b_sequence_start << 13 )|
                          ( b_start_slice << 12 )|
                          ( i == i_count - 1 ? 1 << 11 : 0 )|
                          ( i_picture_coding_type << 8 )|
                          ( i_fbv << 7 )|( i_bfc << 4 )|( i_ffv << 3 )|i_ffc;

        /* rtp common header */
        rtp_packetize_common( id, out, (i == i_count - 1)?1:0,
                          in->i_pts != VLC_TICK_INVALID ? in->i_pts : in->i_dts );

        SetDWBE( out->p_buffer + 12, h );

        memcpy( &out->p_buffer[16], p_data, i_payload );

        out->i_dts    = in->i_dts + i * in->i_length / i_count;
        out->i_length = in->i_length / i_count;

        rtp_packetize_send( id, out );

        p_data += i_payload;
        i_data -= i_payload;
    }

    block_Release(in);
    return VLC_SUCCESS;
}