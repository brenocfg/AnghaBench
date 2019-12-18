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
typedef  int /*<<< orphan*/  sout_stream_id_sys_t ;
struct TYPE_7__ {int* p_buffer; size_t i_buffer; scalar_t__ i_length; scalar_t__ i_pts; scalar_t__ i_dts; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 TYPE_1__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_Release (TYPE_1__*) ; 
 int /*<<< orphan*/  memcpy (int*,int const*,size_t) ; 
 size_t rtp_mtu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtp_packetize_common (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  rtp_packetize_send (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int rtp_packetize_t140( sout_stream_id_sys_t *id, block_t *in )
{
    const size_t   i_max  = rtp_mtu (id);
    const uint8_t *p_data = in->p_buffer;
    size_t         i_data = in->i_buffer;

    for( unsigned i_packet = 0; i_data > 0; i_packet++ )
    {
        size_t i_payload = i_data;

        /* Make sure we stop on an UTF-8 character boundary
         * (assuming the input is valid UTF-8) */
        if( i_data > i_max )
        {
            i_payload = i_max;

            while( ( p_data[i_payload] & 0xC0 ) == 0x80 )
            {
                if( i_payload == 0 )
                 {
                    block_Release(in);
                    return VLC_SUCCESS; /* fishy input! */
                }
                i_payload--;
            }
        }

        block_t *out = block_Alloc( 12 + i_payload );
        if( out == NULL )
        {
            block_Release(in);
            return VLC_SUCCESS;
        }

        rtp_packetize_common( id, out, 0, in->i_pts + i_packet );
        memcpy( out->p_buffer + 12, p_data, i_payload );

        out->i_dts    = in->i_pts;
        out->i_length = 0;

        rtp_packetize_send( id, out );

        p_data += i_payload;
        i_data -= i_payload;
    }

    block_Release(in);
    return VLC_SUCCESS;
}