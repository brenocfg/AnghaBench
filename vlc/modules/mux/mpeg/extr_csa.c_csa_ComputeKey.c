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
 int* key_perm ; 

__attribute__((used)) static void csa_ComputeKey( uint8_t kk[57], uint8_t ck[8] )
{
    int i,j,k;
    int bit[64];
    int newbit[64];
    int kb[8][9];

    /* from a cw create 56 key bytes, here kk[1..56] */

    /* load ck into kb[7][1..8] */
    for( i = 0; i < 8; i++ )
    {
        kb[7][i+1] = ck[i];
    }

    /* calculate all kb[6..1][*] */
    for( i = 0; i < 7; i++ )
    {
        /* do a 64 bit perm on kb */
        for( j = 0; j < 8; j++ )
        {
            for( k = 0; k < 8; k++ )
            {
                bit[j*8+k] = (kb[7-i][1+j] >> (7-k)) & 1;
                newbit[key_perm[j*8+k]-1] = bit[j*8+k];
            }
        }
        for( j = 0; j < 8; j++ )
        {
            kb[6-i][1+j] = 0;
            for( k = 0; k < 8; k++ )
            {
                kb[6-i][1+j] |= newbit[j*8+k] << (7-k);
            }
        }
    }

    /* xor to give kk */
    for( i = 0; i < 7; i++ )
    {
        for( j = 0; j < 8; j++ )
        {
            kk[1+i*8+j] = kb[1+i][1+j] ^ i;
        }
    }
}