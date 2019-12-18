#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_4__ {int* o_ck; int* o_kk; int* e_ck; int* e_kk; } ;
typedef  TYPE_1__ csa_t ;

/* Variables and functions */
 int /*<<< orphan*/  csa_BlockDecypher (int*,int*,int*) ; 
 int /*<<< orphan*/  csa_StreamCypher (TYPE_1__*,int,int*,int*,int*) ; 

void csa_Decrypt( csa_t *c, uint8_t *pkt, int i_pkt_size )
{
    uint8_t *ck;
    uint8_t *kk;

    uint8_t  ib[8], stream[8], block[8];

    int     i_hdr, i_residue;
    int     i, j, n;

    /* transport scrambling control */
    if( (pkt[3]&0x80) == 0 )
    {
        /* not scrambled */
        return;
    }
    if( pkt[3]&0x40 )
    {
        ck = c->o_ck;
        kk = c->o_kk;
    }
    else
    {
        ck = c->e_ck;
        kk = c->e_kk;
    }

    /* clear transport scrambling control */
    pkt[3] &= 0x3f;

    i_hdr = 4;
    if( pkt[3]&0x20 )
    {
        /* skip adaption field */
        i_hdr += pkt[4] + 1;
    }

    if( 188 - i_hdr < 8 )
        return;

    /* init csa state */
    csa_StreamCypher( c, 1, ck, &pkt[i_hdr], ib );

    /* */
    n = (i_pkt_size - i_hdr) / 8;
    if( n < 0 )
        return;
 
    i_residue = (i_pkt_size - i_hdr) % 8;
    for( i = 1; i < n + 1; i++ )
    {
        csa_BlockDecypher( kk, ib, block );
        if( i != n )
        {
            csa_StreamCypher( c, 0, ck, NULL, stream );
            for( j = 0; j < 8; j++ )
            {
                /* xor ib with stream */
                ib[j] = pkt[i_hdr+8*i+j] ^ stream[j];
            }
        }
        else
        {
            /* last block */
            for( j = 0; j < 8; j++ )
            {
                ib[j] = 0;
            }
        }
        /* xor ib with block */
        for( j = 0; j < 8; j++ )
        {
            pkt[i_hdr+8*(i-1)+j] = ib[j] ^ block[j];
        }
    }

    if( i_residue > 0 )
    {
        csa_StreamCypher( c, 0, ck, NULL, stream );
        for( j = 0; j < i_residue; j++ )
        {
            pkt[i_pkt_size - i_residue + j] ^= stream[j];
        }
    }
}