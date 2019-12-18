#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int uint16_t ;
struct TYPE_5__ {int i_buffer; int* p_buffer; scalar_t__ i_pts; scalar_t__ i_dts; } ;
typedef  TYPE_1__ block_t ;

/* Variables and functions */
 int DV_NTSC_FRAME_SIZE ; 
 int DV_PAL_FRAME_SIZE ; 
 scalar_t__ VLC_TICK_INVALID ; 
 TYPE_1__* block_Alloc (int) ; 
 int dv_audio_12to16 (int) ; 
 int** dv_audio_shuffle525 ; 
 int** dv_audio_shuffle625 ; 
 int dv_get_audio_sample_count (int*,int const) ; 

__attribute__((used)) static inline block_t *dv_extract_audio( block_t *p_frame_block )
{
    block_t *p_block;
    uint8_t *p_frame, *p_buf;
    int i_audio_quant, i_samples, i_half_ch;
    const uint16_t (*audio_shuffle)[9];
    int i, j, d, of;

    if( p_frame_block->i_buffer < 4 )
        return NULL;
    const int i_dsf = (p_frame_block->p_buffer[3] & 0x80) >> 7;
    if( p_frame_block->i_buffer < (i_dsf ? DV_PAL_FRAME_SIZE
                                         : DV_NTSC_FRAME_SIZE ) )
        return NULL;

    /* Beginning of AAUX pack */
    p_buf = p_frame_block->p_buffer + 80*6+80*16*3 + 3;
    if( *p_buf != 0x50 ) return NULL;

    i_audio_quant = p_buf[4] & 0x07; /* 0 - 16bit, 1 - 12bit */
    if( i_audio_quant > 1 )
        return NULL;

    i_samples = dv_get_audio_sample_count( &p_buf[1], i_dsf );

    p_block = block_Alloc( 4 * i_samples );

    /* for each DIF segment */
    p_frame = p_frame_block->p_buffer;
    audio_shuffle = i_dsf ? dv_audio_shuffle625 : dv_audio_shuffle525;
    i_half_ch = (i_dsf ? 12 : 10)/2;
    for( i = 0; i < (i_dsf ? 12 : 10); i++ )
    {
        p_frame += 6 * 80; /* skip DIF segment header */

        if( i_audio_quant == 1 && i == i_half_ch ) break;

        for( j = 0; j < 9; j++ )
        {
            for( d = 8; d < 80; d += 2 )
            {
                if( i_audio_quant == 0 )
                {
                    /* 16bit quantization */
                    of = audio_shuffle[i][j] + (d - 8) / 2 *
                           (i_dsf ? 108 : 90);

                    if( of * 2 >= 4 * i_samples ) continue;

                    /* big endian */
                    p_block->p_buffer[of*2] = p_frame[d+1];
                    p_block->p_buffer[of*2+1] = p_frame[d];

                    if( p_block->p_buffer[of*2+1] == 0x80 &&
                        p_block->p_buffer[of*2] == 0x00 )
                        p_block->p_buffer[of*2+1] = 0;
                }
                else
                {
                    /* 12bit quantization */
                    uint16_t lc = (p_frame[d+0] << 4) | (p_frame[d+2] >> 4);
                    uint16_t rc = (p_frame[d+1] << 4) | (p_frame[d+2] & 0x0f);

                    lc = lc == 0x800 ? 0 : dv_audio_12to16(lc);
                    rc = rc == 0x800 ? 0 : dv_audio_12to16(rc);

                    of = audio_shuffle[i][j] + (d - 8) / 3 * (i_dsf ? 108 : 90);
                    if( of*2 >= 4 * i_samples )
                        continue;
                    p_block->p_buffer[of*2+0] = lc & 0xff;
                    p_block->p_buffer[of*2+1] = lc >> 8;

                    of = audio_shuffle[i + i_half_ch][j] + (d - 8) / 3 * (i_dsf ? 108 : 90);
                    if( of*2 >= 4 * i_samples )
                        continue;
                    p_block->p_buffer[of*2+0] = rc & 0xff;
                    p_block->p_buffer[of*2+1] = rc >> 8;

                    ++d;
                }
            }

            p_frame += 16 * 80; /* 15 Video DIFs + 1 Audio DIF */
        }
    }

    p_block->i_pts = p_frame_block->i_pts != VLC_TICK_INVALID ? p_frame_block->i_pts
                                                           : p_frame_block->i_dts;
    p_block->i_dts = p_frame_block->i_dts;
    return p_block;
}