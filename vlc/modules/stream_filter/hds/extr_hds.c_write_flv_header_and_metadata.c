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
typedef  int /*<<< orphan*/  uint8_t ;

/* Variables and functions */
 size_t FLV_FILE_HEADER_LEN ; 
 size_t FLV_TAG_HEADER_LEN ; 
 int /*<<< orphan*/  SCRIPT_TAG ; 
 int /*<<< orphan*/  const* flv_header_bytes ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  memset (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  write_int_24 (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  write_int_32 (int /*<<< orphan*/ *,size_t) ; 

__attribute__((used)) static size_t write_flv_header_and_metadata(
    uint8_t **pp_buffer,
    const uint8_t *p_metadata_payload,
    size_t metadata_payload_len )
{
    size_t metadata_packet_len;
    if ( metadata_payload_len > 0 && p_metadata_payload )
        metadata_packet_len = FLV_TAG_HEADER_LEN + metadata_payload_len;
    else
        metadata_packet_len = 0;
    size_t data_len = FLV_FILE_HEADER_LEN + metadata_packet_len;

    *pp_buffer = malloc( data_len );
    if ( ! *pp_buffer )
    {
        return 0;
    }

    // FLV file header
    memcpy( *pp_buffer, flv_header_bytes, FLV_FILE_HEADER_LEN );

    if ( metadata_packet_len > 0 )
    {
        uint8_t *p = *pp_buffer + FLV_FILE_HEADER_LEN;

        // tag type
        *p = SCRIPT_TAG;
        p++;

        // payload size
        write_int_24( p, metadata_payload_len );
        p += 3;

        // timestamp and stream id
        memset( p, 0, 7 );
        p += 7;

        // metadata payload
        memcpy( p, p_metadata_payload, metadata_payload_len );
        p += metadata_payload_len;

        // packet payload size
        write_int_32( p, metadata_packet_len );
    }

    return data_len;
}