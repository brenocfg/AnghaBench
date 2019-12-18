#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_guid_t ;
typedef  int /*<<< orphan*/  var_buffer_t ;
typedef  size_t uint8_t ;
typedef  int uint64_t ;
typedef  int int16_t ;
struct TYPE_5__ {TYPE_1__* stream; void* i_min_data_packet_size; void* i_data_packets_count; void* i_file_size; } ;
typedef  TYPE_2__ asf_header_t ;
struct TYPE_4__ {int i_bitrate; void* i_cat; scalar_t__ i_selected; } ;

/* Variables and functions */
 void* ASF_CODEC_TYPE_AUDIO ; 
 void* ASF_CODEC_TYPE_UNKNOWN ; 
 void* ASF_CODEC_TYPE_VIDEO ; 
 int /*<<< orphan*/  asf_object_extended_stream_properties_guid ; 
 int /*<<< orphan*/  asf_object_file_properties_guid ; 
 int /*<<< orphan*/  asf_object_header_extension_guid ; 
 int /*<<< orphan*/  asf_object_header_guid ; 
 int /*<<< orphan*/  asf_object_stream_bitrate_properties ; 
 int /*<<< orphan*/  asf_object_stream_properties_guid ; 
 int /*<<< orphan*/  asf_object_stream_type_audio ; 
 int /*<<< orphan*/  asf_object_stream_type_video ; 
 scalar_t__ guidcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int var_buffer_get16 (int /*<<< orphan*/ *) ; 
 void* var_buffer_get32 (int /*<<< orphan*/ *) ; 
 void* var_buffer_get64 (int /*<<< orphan*/ *) ; 
 int var_buffer_get8 (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_buffer_getguid (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  var_buffer_getmemory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  var_buffer_initread (int /*<<< orphan*/ *,size_t*,int) ; 
 scalar_t__ var_buffer_readempty (int /*<<< orphan*/ *) ; 

void  asf_HeaderParse ( asf_header_t *hdr,
                            uint8_t *p_header, int i_header )
{
    var_buffer_t buffer;
    vlc_guid_t  guid;
    uint64_t    i_size;

    hdr->i_file_size = 0;
    hdr->i_data_packets_count = 0;
    hdr->i_min_data_packet_size = 0;
    for( unsigned i = 0; i < 128; i++ )
    {
        hdr->stream[i].i_cat = ASF_CODEC_TYPE_UNKNOWN;
        hdr->stream[i].i_selected = 0;
        hdr->stream[i].i_bitrate = -1;
    }

    var_buffer_initread( &buffer, p_header, i_header );
    var_buffer_getguid( &buffer, &guid );

    if( !guidcmp( &guid, &asf_object_header_guid ) )
    {
        /* ERROR: */
    }
    var_buffer_getmemory( &buffer, NULL, 30 - 16 );

    for( ;; )
    {
        var_buffer_getguid( &buffer, &guid );
        i_size = var_buffer_get64( &buffer );

        if( guidcmp( &guid, &asf_object_file_properties_guid ) )
        {
            var_buffer_getmemory( &buffer, NULL, 16 );
            hdr->i_file_size            = var_buffer_get64( &buffer );
            var_buffer_getmemory( &buffer, NULL, 8 );
            hdr->i_data_packets_count   = var_buffer_get64( &buffer );
            var_buffer_getmemory( &buffer, NULL, 8+8+8+4);
            hdr->i_min_data_packet_size = var_buffer_get32( &buffer );

            var_buffer_getmemory( &buffer, NULL, i_size - 24 - 16 - 8 - 8 - 8 - 8-8-8-4 - 4);
        }
        else if( guidcmp( &guid, &asf_object_header_extension_guid ) )
        {
            /* Enter it */
            var_buffer_getmemory( &buffer, NULL, 46 - 24 );
        }
        else if( guidcmp( &guid, &asf_object_extended_stream_properties_guid ) )
        {
            /* Grrrrrr */
            int16_t i_count1, i_count2;
            int i_subsize;

            var_buffer_getmemory( &buffer, NULL, 84 - 24 );

            i_count1 = var_buffer_get16( &buffer );
            i_count2 = var_buffer_get16( &buffer );

            i_subsize = 88;
            for( int i = 0; i < i_count1; i++ )
            {
                int i_len;

                var_buffer_get16( &buffer );
                i_len = var_buffer_get16( &buffer );
                var_buffer_getmemory( &buffer, NULL, i_len );

                i_subsize += 4 + i_len;
            }

            for( int i = 0; i < i_count2; i++ )
            {
                int i_len;
                var_buffer_getmemory( &buffer, NULL, 16 + 2 );
                i_len = var_buffer_get32( &buffer );
                var_buffer_getmemory( &buffer, NULL, i_len );

                i_subsize += 16 + 6 + i_len;
            }

            if( i_size - i_subsize <= 24 )
            {
                var_buffer_getmemory( &buffer, NULL, i_size - i_subsize );
            }
            /* It's a hack we just skip the first part of the object until
             * the embed stream properties if any (ugly, but whose fault ?) */
        }
        else if( guidcmp( &guid, &asf_object_stream_properties_guid ) )
        {
            int     i_stream_id;
            vlc_guid_t  stream_type;

            var_buffer_getguid( &buffer, &stream_type );
            var_buffer_getmemory( &buffer, NULL, 32 );

            i_stream_id = var_buffer_get8( &buffer ) & 0x7f;
            var_buffer_getmemory( &buffer, NULL, i_size - 24 - 32 - 16 - 1);

            if( guidcmp( &stream_type, &asf_object_stream_type_video ) )
            {
                hdr->stream[i_stream_id].i_cat = ASF_CODEC_TYPE_VIDEO;
            }
            else if( guidcmp( &stream_type, &asf_object_stream_type_audio ) )
            {
                hdr->stream[i_stream_id].i_cat = ASF_CODEC_TYPE_AUDIO;
            }
            else
            {
                hdr->stream[i_stream_id].i_cat = ASF_CODEC_TYPE_UNKNOWN;
            }
        }
        else if ( guidcmp( &guid, &asf_object_stream_bitrate_properties ) )
        {
            int     i_count;
            uint8_t i_stream_id;

            i_count = var_buffer_get16( &buffer );
            i_size -= 2;
            while( i_count > 0 )
            {
                i_stream_id = var_buffer_get16( &buffer )&0x7f;
                hdr->stream[i_stream_id].i_bitrate =  var_buffer_get32( &buffer );
                i_count--;
                i_size -= 6;
            }
            var_buffer_getmemory( &buffer, NULL, i_size - 24 );
        }
        else
        {
            // skip unknown guid
            var_buffer_getmemory( &buffer, NULL, i_size - 24 );
        }

        if( var_buffer_readempty( &buffer ) )
            return;
    }
}