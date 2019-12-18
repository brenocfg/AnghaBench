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
 int* block_perm ; 
 int* block_sbox ; 

__attribute__((used)) static void csa_BlockCypher( uint8_t kk[57], uint8_t bd[8], uint8_t ib[8] )
{
    int i;
    int perm_out;
    int R[9];
    int next_R1;

    for( i = 0; i < 8; i++ )
    {
        R[i+1] = bd[i];
    }

    // loop over kk[1]..kk[56]
    for( i = 1; i <= 56; i++ )
    {
        const int sbox_out = block_sbox[ kk[i]^R[8] ];
        perm_out = block_perm[sbox_out];

        next_R1 = R[2];
        R[2] = R[3] ^ R[1];
        R[3] = R[4] ^ R[1];
        R[4] = R[5] ^ R[1];
        R[5] = R[6];
        R[6] = R[7] ^ perm_out;
        R[7] = R[8];
        R[8] = R[1] ^ sbox_out;

        R[1] = next_R1;
    }

    for( i = 0; i < 8; i++ )
    {
        ib[i] = R[i+1];
    }
}