#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int uint32_t ;
struct TYPE_11__ {int i_nb_inputs; TYPE_3__** pp_inputs; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_mux_t ;
struct TYPE_12__ {int i_psm_version; int* crc32_table; } ;
typedef  TYPE_2__ sout_mux_sys_t ;
struct TYPE_13__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ sout_input_t ;
struct TYPE_14__ {scalar_t__* lang; int i_stream_type; int i_stream_id; } ;
typedef  TYPE_4__ ps_stream_t ;
struct TYPE_15__ {int* p_buffer; size_t i_buffer; int /*<<< orphan*/  i_pts; int /*<<< orphan*/  i_dts; } ;
typedef  TYPE_5__ block_t ;
typedef  int /*<<< orphan*/  bits_buffer_t ;

/* Variables and functions */
 int /*<<< orphan*/  bits_initwrite (int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  bits_write (int /*<<< orphan*/ *,int,int) ; 
 TYPE_5__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_ChainAppend (TYPE_5__**,TYPE_5__*) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static void MuxWritePSM( sout_mux_t *p_mux, block_t **p_buf, vlc_tick_t i_dts )
{
    sout_mux_sys_t *p_sys = p_mux->p_sys;
    block_t *p_hdr;
    bits_buffer_t bits;
    int i, i_psm_size = 16, i_es_map_size = 0;

    for( i = 0; i < p_mux->i_nb_inputs; i++ )
    {
        sout_input_t *p_input = p_mux->pp_inputs[i];
        ps_stream_t *p_stream = p_input->p_sys;

        i_es_map_size += 4;
        if( p_stream->lang[0] != 0 ) i_es_map_size += 6;
    }

    i_psm_size += i_es_map_size;

    p_hdr = block_Alloc( i_psm_size );
    if( !p_hdr )
        return;
    p_hdr->i_dts = p_hdr->i_pts = i_dts;

    memset( p_hdr->p_buffer, 0, p_hdr->i_buffer );
    bits_initwrite( &bits, i_psm_size, p_hdr->p_buffer );
    bits_write( &bits, 32, 0x01bc );
    bits_write( &bits, 16, i_psm_size - 6 );
    bits_write( &bits, 1, 1 ); /* current_next_indicator */
    bits_write( &bits, 2, 0xF ); /* reserved */
    bits_write( &bits, 5, p_sys->i_psm_version );
    bits_write( &bits, 7, 0xFF ); /* reserved */
    bits_write( &bits, 1, 1 ); /* marker */

    bits_write( &bits, 16, 0 ); /* program_stream_info_length */
    /* empty */

    bits_write( &bits, 16, i_es_map_size ); /* elementary_stream_map_length */
    for( i = 0; i < p_mux->i_nb_inputs; i++ )
    {
        sout_input_t *p_input = p_mux->pp_inputs[i];
        ps_stream_t *p_stream = p_input->p_sys;

        bits_write( &bits, 8, p_stream->i_stream_type ); /* stream_type */
        bits_write( &bits, 8, p_stream->i_stream_id ); /* elementary_stream_id */

        /* ISO639 language descriptor */
        if( p_stream->lang[0] != 0 )
        {
            bits_write( &bits, 16, 6 ); /* elementary_stream_info_length */

            bits_write( &bits, 8, 0x0a ); /* descriptor_tag */
            bits_write( &bits, 8, 4 ); /* descriptor_length */

            bits_write( &bits, 8, p_stream->lang[0] );
            bits_write( &bits, 8, p_stream->lang[1] );
            bits_write( &bits, 8, p_stream->lang[2] );
            bits_write( &bits, 8, 0 ); /* audio type: 0x00 undefined */
        }
        else
        {
            bits_write( &bits, 16, 0 ); /* elementary_stream_info_length */
        }
    }

    /* CRC32 */
    {
        uint32_t i_crc = 0xffffffff;
        for( i = 0; (size_t)i < p_hdr->i_buffer; i++ )
        i_crc = (i_crc << 8) ^
            p_sys->crc32_table[((i_crc >> 24) ^ p_hdr->p_buffer[i]) & 0xff];

        bits_write( &bits, 32, i_crc );
    }

    block_ChainAppend( p_buf, p_hdr );
}