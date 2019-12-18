#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint32_t ;
struct TYPE_6__ {int* p_buffer; scalar_t__ i_buffer; } ;
typedef  TYPE_1__ block_t ;
struct TYPE_7__ {unsigned int i_channels; int i_bits; unsigned int* pi_position; } ;
typedef  TYPE_2__ aob_group_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int vlc_bswap32 (int) ; 

__attribute__((used)) static void AobExtract( block_t *p_aout_buffer,
                        block_t *p_block, unsigned i_aoutbits, aob_group_t p_group[2] )
{
    uint8_t *p_out = p_aout_buffer->p_buffer;
    const unsigned i_total_channels = p_group[0].i_channels +
                                      ( p_group[1].i_bits ? p_group[1].i_channels : 0 );

    while( p_block->i_buffer > 0 )
    {
        unsigned int i_aout_written = 0;

        for( int i = 0; i < 2; i++ )
        {
            const aob_group_t *g = &p_group[1-i];
            const unsigned int i_group_size = 2 * g->i_channels * g->i_bits / 8;

            if( p_block->i_buffer < i_group_size )
            {
                p_block->i_buffer = 0;
                break;
            }

            if( !g->i_bits )
                continue;

            for( unsigned n = 0; n < 2; n++ )
            {
                for( unsigned j = 0; j < g->i_channels; j++ )
                {
                    const int i_src = n * g->i_channels + j;
                    const int i_dst = n * i_total_channels + g->pi_position[j];
                    uint32_t *p_out32 = (uint32_t *) &p_out[4*i_dst];

                    if( g->i_bits == 24 )
                    {
                        assert( i_aoutbits == 32 );
                        *p_out32 = (p_block->p_buffer[2*i_src+0] << 24)
                                 | (p_block->p_buffer[2*i_src+1] << 16)
                                 | (p_block->p_buffer[4*g->i_channels+i_src] <<  8);
#ifdef WORDS_BIGENDIAN
                        *p_out32 = vlc_bswap32(*p_out32);
#endif
                        i_aout_written += 4;
                    }
                    else if( g->i_bits == 20 )
                    {
                        assert( i_aoutbits == 32 );
                        *p_out32 = (p_block->p_buffer[2*i_src+0] << 24)
                                 | (p_block->p_buffer[2*i_src+1] << 16)
                                 | (((p_block->p_buffer[4*g->i_channels+i_src] << ((!n)?0:4) ) & 0xf0) <<  8);
#ifdef WORDS_BIGENDIAN
                        *p_out32 = vlc_bswap32(*p_out32);
#endif
                        i_aout_written += 4;
                    }
                    else
                    {
                        assert( g->i_bits == 16 );
                        assert( i_aoutbits == 16 || i_aoutbits == 32 );
                        if( i_aoutbits == 16 )
                        {
#ifdef WORDS_BIGENDIAN
                            memcpy( &p_out[2*i_dst], &p_block->p_buffer[2*i_src], 2 );
#else
                            p_out[2*i_dst+1] = p_block->p_buffer[2*i_src+0];
                            p_out[2*i_dst+0] = p_block->p_buffer[2*i_src+1];
#endif
                            i_aout_written += 2;
                        }
                        else
                        {
                            *p_out32 = (p_block->p_buffer[2*i_src+0] << 24)
                                     | (p_block->p_buffer[2*i_src+1] << 16);
#ifdef WORDS_BIGENDIAN
                            *p_out32 = vlc_bswap32(*p_out32);
#endif
                            i_aout_written += 4;
                        }
                    }
                }
            }

            /* */
            p_block->i_buffer -= i_group_size;
            p_block->p_buffer += i_group_size;
        }
        p_out += i_aout_written;
    }
}