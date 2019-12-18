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
 int __MIN (int,int) ; 

__attribute__((used)) static int Buf14To16( uint8_t *p_out, const uint8_t *p_in, int i_in, int i_le,
                      int i_out_le )
{
    unsigned char tmp, cur = 0;
    int bits_in, bits_out = 0;
    int i, i_out = 0;

    for( i = 0; i < i_in; i++  )
    {
        if( i%2 )
        {
            tmp = p_in[i-i_le];
            bits_in = 8;
        }
        else
        {
            tmp = p_in[i+i_le] & 0x3F;
            bits_in = 8 - 2;
        }

        if( bits_out < 8 )
        {
            int need = __MIN( 8 - bits_out, bits_in );
            cur <<= need;
            cur |= ( tmp >> (bits_in - need) );
            tmp <<= (8 - bits_in + need);
            tmp >>= (8 - bits_in + need);
            bits_in -= need;
            bits_out += need;
        }

        if( bits_out == 8 )
        {
            if( i_out % 2 )
                p_out[i_out - i_out_le] = cur;
            else
                p_out[i_out + i_out_le] = cur;
            cur = 0;
            bits_out = 0;
            i_out++;
        }

        bits_out += bits_in;
        cur <<= bits_in;
        cur |= tmp;
    }

    return i_out;
}