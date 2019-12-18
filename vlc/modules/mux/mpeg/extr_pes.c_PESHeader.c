#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int int64_t ;
struct TYPE_7__ {int /*<<< orphan*/  i_cat; int /*<<< orphan*/  i_codec; } ;
typedef  TYPE_1__ es_format_t ;
struct TYPE_8__ {int i_data; } ;
typedef  TYPE_2__ bits_buffer_t ;

/* Variables and functions */
#define  PES_DSMCC_STREAM 135 
#define  PES_ECM 134 
#define  PES_EMM 133 
 int PES_EXTENDED_STREAM_ID ; 
#define  PES_ITU_T_H222_1_TYPE_E_STREAM 132 
#define  PES_PADDING 131 
 int PES_PAYLOAD_SIZE_MAX ; 
 int PES_PRIVATE_STREAM_1 ; 
#define  PES_PRIVATE_STREAM_2 130 
#define  PES_PROGRAM_STREAM_DIRECTORY 129 
#define  PES_PROGRAM_STREAM_MAP 128 
 int /*<<< orphan*/  VIDEO_ES ; 
 int /*<<< orphan*/  VLC_CODEC_MP1V ; 
 int /*<<< orphan*/  VLC_CODEC_MP2V ; 
 int /*<<< orphan*/  VLC_CODEC_MPGV ; 
 int /*<<< orphan*/  bits_align (TYPE_2__*) ; 
 int /*<<< orphan*/  bits_initwrite (TYPE_2__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bits_write (TYPE_2__*,int,int) ; 

__attribute__((used)) static inline int PESHeader( uint8_t *p_hdr, int64_t i_pts, int64_t i_dts,
                             int i_es_size, const es_format_t *p_fmt,
                             int i_stream_id, bool b_mpeg2,
                             bool b_data_alignment, int i_header_size )
{
    bits_buffer_t bits;
    int     i_extra = 0;
    int i_private_id = -1;
    int i_stream_id_extension = 0;

    /* HACK for private stream 1 in ps */
    if( ( i_stream_id >> 8 ) == PES_PRIVATE_STREAM_1 )
    {
        i_private_id = i_stream_id & 0xff;
        i_stream_id = PES_PRIVATE_STREAM_1;
        /* For PES_PRIVATE_STREAM_1 there is an extra header after the
           pes header */
        /* i_private_id != -1 because TS use 0xbd without private_id */
        i_extra = 1;
        if( ( i_private_id & 0xf0 ) == 0x80 )
            i_extra += 3;
    }
    else if( ( i_stream_id >> 8 ) == PES_EXTENDED_STREAM_ID )
    {
        /* Enable support for extended_stream_id as defined in
         * ISO/IEC 13818-1:2000/Amd.2:2003 */
        /* NB, i_extended_stream_id is limited to 7 bits */
        i_stream_id_extension = i_stream_id & 0x7f;
        i_stream_id = PES_EXTENDED_STREAM_ID;
    }

    bits_initwrite( &bits, 50, p_hdr );

    /* add start code */
    bits_write( &bits, 24, 0x01 );
    bits_write( &bits, 8, i_stream_id );
    switch( i_stream_id )
    {
        case PES_PROGRAM_STREAM_MAP:
        case PES_PADDING:
        case PES_PRIVATE_STREAM_2:
        case PES_ECM:
        case PES_EMM:
        case PES_PROGRAM_STREAM_DIRECTORY:
        case PES_DSMCC_STREAM:
        case PES_ITU_T_H222_1_TYPE_E_STREAM:
            /* add pes data size  */
            bits_write( &bits, 16, i_es_size );
            bits_align( &bits );
            return( bits.i_data );

        default:
            /* arg, a little more difficult */
            if( b_mpeg2 )
            {
                int i_pts_dts;
                bool b_pes_extension_flag = false;

                if( i_pts > 0 && i_dts > 0 &&
                    ( i_pts != i_dts || ( p_fmt->i_cat == VIDEO_ES &&
                      p_fmt->i_codec != VLC_CODEC_MPGV &&
                      p_fmt->i_codec != VLC_CODEC_MP2V &&
                      p_fmt->i_codec != VLC_CODEC_MP1V 
                      ) ) )
                {
                    i_pts_dts = 0x03;
                    if ( !i_header_size ) i_header_size = 0xa;
                }
                else if( i_pts > 0 )
                {
                    i_pts_dts = 0x02;
                    if ( !i_header_size ) i_header_size = 0x5;
                }
                else
                {
                    i_pts_dts = 0x00;
                    if ( !i_header_size ) i_header_size = 0x0;
                }

                if( i_stream_id == PES_EXTENDED_STREAM_ID )
                {
                    b_pes_extension_flag = true;
                    i_header_size += 1 + 1;
                }

                if( b_pes_extension_flag )
                {
                    i_header_size += 1;
                }

                /* Unbounded streams are only allowed in TS (not PS) and only
                 * for some ES, eg. MPEG* Video ES or Dirac ES. */
                if( i_es_size > PES_PAYLOAD_SIZE_MAX )
                    bits_write( &bits, 16, 0 ); // size unbounded
                else
                    bits_write( &bits, 16, i_es_size + i_extra + 3
                                 + i_header_size ); // size
                bits_write( &bits, 2, 0x02 ); // mpeg2 id
                bits_write( &bits, 2, 0x00 ); // pes scrambling control
                bits_write( &bits, 1, 0x00 ); // pes priority
                bits_write( &bits, 1, b_data_alignment ); // data alignement indicator
                bits_write( &bits, 1, 0x00 ); // copyright
                bits_write( &bits, 1, 0x00 ); // original or copy

                bits_write( &bits, 2, i_pts_dts ); // pts_dts flags
                bits_write( &bits, 1, 0x00 ); // escr flags
                bits_write( &bits, 1, 0x00 ); // es rate flag
                bits_write( &bits, 1, 0x00 ); // dsm trick mode flag
                bits_write( &bits, 1, 0x00 ); // additional copy info flag
                bits_write( &bits, 1, 0x00 ); // pes crc flag
                bits_write( &bits, 1, b_pes_extension_flag );
                bits_write( &bits, 8, i_header_size );

                /* write pts */
                if( i_pts_dts & 0x02 )
                {
                    bits_write( &bits, 4, i_pts_dts ); // '0010' or '0011'
                    bits_write( &bits, 3, i_pts >> 30 );
                    bits_write( &bits, 1, 0x01 ); // marker
                    bits_write( &bits, 15, i_pts >> 15 );
                    bits_write( &bits, 1, 0x01 ); // marker
                    bits_write( &bits, 15, i_pts );
                    bits_write( &bits, 1, 0x01 ); // marker
                    i_header_size -= 0x5;
                }
                /* write i_dts */
                if( i_pts_dts & 0x01 )
                {
                    bits_write( &bits, 4, 0x01 ); // '0001'
                    bits_write( &bits, 3, i_dts >> 30 );
                    bits_write( &bits, 1, 0x01 ); // marker
                    bits_write( &bits, 15, i_dts >> 15 );
                    bits_write( &bits, 1, 0x01 ); // marker
                    bits_write( &bits, 15, i_dts );
                    bits_write( &bits, 1, 0x01 ); // marker
                    i_header_size -= 0x5;
                }
                if( b_pes_extension_flag )
                {
                    bits_write( &bits, 1, 0x00 ); // PES_private_data_flag
                    bits_write( &bits, 1, 0x00 ); // pack_header_field_flag
                    bits_write( &bits, 1, 0x00 ); // program_packet_sequence_counter_flag
                    bits_write( &bits, 1, 0x00 ); // P-STD_buffer_flag
                    bits_write( &bits, 3, 0x07 ); // reserved
                    bits_write( &bits, 1, 0x01 ); // PES_extension_flag_2
                    /* skipping unsupported parts: */
                    /*   PES_private_data */
                    /*   pack_header */
                    /*   program_packet_sequence_counter */
                    /*   P-STD_buffer_flag */
                    if( i_stream_id == PES_EXTENDED_STREAM_ID )
                    {
                        /* PES_extension_2 */
                        bits_write( &bits, 1, 0x01 ); // marker
                        bits_write( &bits, 7, 0x01 ); // PES_extension_field_length
                        bits_write( &bits, 1, 0x01 ); // stream_id_extension_flag
                        bits_write( &bits, 7, i_stream_id_extension );
                        i_header_size -= 0x2;
                    }
                    i_header_size -= 0x1;
                }
                while ( i_header_size )
                {
                    bits_write( &bits, 8, 0xff );
                    i_header_size--;
                }
            }
            else /* MPEG1 */
            {
                int i_pts_dts;

                if( i_pts > 0 && i_dts > 0 &&
                    ( i_pts != i_dts || p_fmt->i_cat == VIDEO_ES ) )
                {
                    bits_write( &bits, 16, i_es_size + i_extra + 10 /* + stuffing */ );
                    i_pts_dts = 0x03;
                }
                else if( i_pts > 0 )
                {
                    bits_write( &bits, 16, i_es_size + i_extra + 5 /* + stuffing */ );
                    i_pts_dts = 0x02;
                }
                else
                {
                    bits_write( &bits, 16, i_es_size + i_extra + 1 /* + stuffing */);
                    i_pts_dts = 0x00;
                }

                /* FIXME: Now should be stuffing */

                /* No STD_buffer_scale and STD_buffer_size */

                /* write pts */
                if( i_pts_dts & 0x02 )
                {
                    bits_write( &bits, 4, i_pts_dts ); // '0010' or '0011'
                    bits_write( &bits, 3, i_pts >> 30 );
                    bits_write( &bits, 1, 0x01 ); // marker
                    bits_write( &bits, 15, i_pts >> 15 );
                    bits_write( &bits, 1, 0x01 ); // marker
                    bits_write( &bits, 15, i_pts );
                    bits_write( &bits, 1, 0x01 ); // marker
                }
                /* write i_dts */
                if( i_pts_dts & 0x01 )
                {
                    bits_write( &bits, 4, 0x01 ); // '0001'
                    bits_write( &bits, 3, i_dts >> 30 );
                    bits_write( &bits, 1, 0x01 ); // marker
                    bits_write( &bits, 15, i_dts >> 15 );
                    bits_write( &bits, 1, 0x01 ); // marker
                    bits_write( &bits, 15, i_dts );
                    bits_write( &bits, 1, 0x01 ); // marker
                }
                if( !i_pts_dts )
                {
                    bits_write( &bits, 8, 0x0F );
                }

            }

            /* now should be stuffing */
            /* and then pes data */

            bits_align( &bits );
            if( i_stream_id == PES_PRIVATE_STREAM_1 && i_private_id != -1 )
            {
                bits_write( &bits, 8, i_private_id );
                if( ( i_private_id&0xf0 ) == 0x80 )
                {
                    bits_write( &bits, 24, 0 ); // ac3
                }
            }
            bits_align( &bits );
            return( bits.i_data );
    }
}