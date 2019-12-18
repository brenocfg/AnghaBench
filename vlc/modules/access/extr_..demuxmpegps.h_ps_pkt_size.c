#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int uint8_t ;

/* Variables and functions */
#define  PS_STREAM_ID_DIRECTORY 132 
#define  PS_STREAM_ID_END_STREAM 131 
#define  PS_STREAM_ID_MAP 130 
#define  PS_STREAM_ID_PACK_HEADER 129 
#define  PS_STREAM_ID_SYSTEM_HEADER 128 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static inline int ps_pkt_size( const uint8_t *p, int i_peek )
{
    if( unlikely(i_peek < 4) )
        return -1;

    switch( p[3] )
    {
        case PS_STREAM_ID_END_STREAM:
            return 4;

        case PS_STREAM_ID_PACK_HEADER:
            if( i_peek > 4 )
            {
                if( i_peek >= 14 && (p[4] >> 6) == 0x01 )
                    return 14 + (p[13]&0x07);
                else if( i_peek >= 12 && (p[4] >> 4) == 0x02 )
                    return 12;
            }
            break;

        case PS_STREAM_ID_SYSTEM_HEADER:
        case PS_STREAM_ID_MAP:
        case PS_STREAM_ID_DIRECTORY:
        default:
            if( i_peek >= 6 )
                return 6 + ((p[4]<<8) | p[5] );
    }
    return -1;
}