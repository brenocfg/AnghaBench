#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
struct TYPE_8__ {int* p_extra; int i_extra; } ;
typedef  TYPE_1__ es_format_t ;
struct TYPE_9__ {size_t i_buffer; int* p_buffer; } ;
typedef  TYPE_2__ block_t ;

/* Variables and functions */
 size_t ADTS_HEADER_SIZE ; 
 TYPE_2__* block_Realloc (TYPE_2__*,size_t,size_t) ; 

__attribute__((used)) static block_t *Add_ADTS( block_t *p_data, const es_format_t *p_fmt )
{
#define ADTS_HEADER_SIZE 7 /* CRC needs 2 more bytes */

    const uint8_t *p_extra = p_fmt->p_extra;

    if( !p_data || p_fmt->i_extra < 2 || !p_extra )
        return p_data; /* no data to construct the headers */

    size_t frame_length = p_data->i_buffer + ADTS_HEADER_SIZE;
    int i_index = ( (p_extra[0] << 1) | (p_extra[1] >> 7) ) & 0x0f;
    int i_profile = (p_extra[0] >> 3) - 1; /* i_profile < 4 */

    if( i_index == 0x0f && p_fmt->i_extra < 5 )
        return p_data; /* not enough data */

    int i_channels = (p_extra[i_index == 0x0f ? 4 : 1] >> 3) & 0x0f;

    block_t *p_new_block = block_Realloc( p_data, ADTS_HEADER_SIZE,
                                            p_data->i_buffer );
    uint8_t *p_buffer = p_new_block->p_buffer;

    /* fixed header */
    p_buffer[0] = 0xff;
    p_buffer[1] = 0xf1; /* 0xf0 | 0x00 | 0x00 | 0x01 */
    p_buffer[2] = (i_profile << 6) | ((i_index & 0x0f) << 2) | ((i_channels >> 2) & 0x01) ;
    p_buffer[3] = (i_channels << 6) | ((frame_length >> 11) & 0x03);

    /* variable header (starts at last 2 bits of 4th byte) */

    int i_fullness = 0x7ff; /* 0x7ff means VBR */
    /* XXX: We should check if it's CBR or VBR, but no known implementation
     * do that, and it's a pain to calculate this field */

    p_buffer[4] = frame_length >> 3;
    p_buffer[5] = ((frame_length & 0x07) << 5) | ((i_fullness >> 6) & 0x1f);
    p_buffer[6] = ((i_fullness & 0x3f) << 2) /* | 0xfc */;

    return p_new_block;
}