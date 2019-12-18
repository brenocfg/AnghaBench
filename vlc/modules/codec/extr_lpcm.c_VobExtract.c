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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_4__ {int* p_buffer; int i_buffer; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (int*,int*,int) ; 
 int /*<<< orphan*/  swab (int*,int*,int) ; 

__attribute__((used)) static void VobExtract( block_t *p_aout_buffer, block_t *p_block,
                        unsigned i_bits )
{
    /* 20/24 bits LPCM use special packing */
    if( i_bits == 24 )
    {
        uint32_t *p_out = (uint32_t *)p_aout_buffer->p_buffer;

        while( p_block->i_buffer / 12 )
        {
            /* Sample 1 */
            *(p_out++) = (p_block->p_buffer[ 0] << 24)
                       | (p_block->p_buffer[ 1] << 16)
                       | (p_block->p_buffer[ 8] <<  8);
            /* Sample 2 */
            *(p_out++) = (p_block->p_buffer[ 2] << 24)
                       | (p_block->p_buffer[ 3] << 16)
                       | (p_block->p_buffer[ 9] <<  8);
            /* Sample 3 */
            *(p_out++) = (p_block->p_buffer[ 4] << 24)
                       | (p_block->p_buffer[ 5] << 16)
                       | (p_block->p_buffer[10] <<  8);
            /* Sample 4 */
            *(p_out++) = (p_block->p_buffer[ 6] << 24)
                       | (p_block->p_buffer[ 7] << 16)
                       | (p_block->p_buffer[11] <<  8);

            p_block->i_buffer -= 12;
            p_block->p_buffer += 12;
        }
    }
    else if( i_bits == 20 )
    {
        uint32_t *p_out = (uint32_t *)p_aout_buffer->p_buffer;

        while( p_block->i_buffer / 10 )
        {
            /* Sample 1 */
            *(p_out++) = ( p_block->p_buffer[0]         << 24)
                       | ( p_block->p_buffer[1]         << 16)
                       | ((p_block->p_buffer[8] & 0xF0) <<  8);
            /* Sample 2 */
            *(p_out++) = ( p_block->p_buffer[2]         << 24)
                       | ( p_block->p_buffer[3]         << 16)
                       | ((p_block->p_buffer[8] & 0x0F) << 12);
            /* Sample 3 */
            *(p_out++) = ( p_block->p_buffer[4]         << 24)
                       | ( p_block->p_buffer[5]         << 16)
                       | ((p_block->p_buffer[9] & 0xF0) <<  8);
            /* Sample 4 */
            *(p_out++) = ( p_block->p_buffer[6]         << 24)
                       | ( p_block->p_buffer[7]         << 16)
                       | ((p_block->p_buffer[9] & 0x0F) << 12);

            p_block->i_buffer -= 10;
            p_block->p_buffer += 10;
        }
    }
    else
    {
        assert( i_bits == 16 );
#ifdef WORDS_BIGENDIAN
        memcpy( p_aout_buffer->p_buffer, p_block->p_buffer, p_block->i_buffer );
#else
        swab( p_block->p_buffer, p_aout_buffer->p_buffer, p_block->i_buffer );
#endif
    }
}