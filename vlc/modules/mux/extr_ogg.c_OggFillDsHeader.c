#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int i_avgbytespersec; int /*<<< orphan*/  i_block_align; int /*<<< orphan*/  i_channels; } ;
struct TYPE_6__ {int i_width; int i_height; } ;
struct TYPE_8__ {TYPE_2__ audio; TYPE_1__ video; } ;
struct TYPE_9__ {int i_default_len; int i_buffer_size; int i_padding_1; int i_size; TYPE_3__ header; int /*<<< orphan*/  i_padding_0; int /*<<< orphan*/  i_bits_per_sample; int /*<<< orphan*/  i_samples_per_unit; int /*<<< orphan*/  i_time_unit; int /*<<< orphan*/ * sub_type; int /*<<< orphan*/ * stream_type; int /*<<< orphan*/  i_packet_type; } ;
typedef  TYPE_4__ oggds_header_t ;
typedef  int int32_t ;

/* Variables and functions */
#define  AUDIO_ES 129 
 int /*<<< orphan*/  SetDWLE (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  SetQWLE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetWLE (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
#define  VIDEO_ES 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int32_t OggFillDsHeader( uint8_t *p_buffer, oggds_header_t *p_oggds_header, int i_cat )
{
    int index = 0;
    p_buffer[index] = p_oggds_header->i_packet_type;
    index++;
    memcpy( &p_buffer[index], p_oggds_header->stream_type, sizeof(p_oggds_header->stream_type) );
    index += sizeof(p_oggds_header->stream_type);
    memcpy(&p_buffer[index], p_oggds_header->sub_type, sizeof(p_oggds_header->sub_type) );
    index += sizeof(p_oggds_header->sub_type);

    /* The size is filled at the end */
    uint8_t *p_isize = &p_buffer[index];
    index += 4;

    SetQWLE( &p_buffer[index], p_oggds_header->i_time_unit );
    index += 8;
    SetQWLE( &p_buffer[index], p_oggds_header->i_samples_per_unit );
    index += 8;
    SetDWLE( &p_buffer[index], p_oggds_header->i_default_len );
    index += 4;
    SetDWLE( &p_buffer[index], p_oggds_header->i_buffer_size );
    index += 4;
    SetWLE( &p_buffer[index], p_oggds_header->i_bits_per_sample );
    index += 2;
    SetWLE( &p_buffer[index], p_oggds_header->i_padding_0 );
    index += 2;
    /* audio or video */
    switch( i_cat )
    {
    case VIDEO_ES:
        SetDWLE( &p_buffer[index], p_oggds_header->header.video.i_width );
        SetDWLE( &p_buffer[index+4], p_oggds_header->header.video.i_height );
        break;
    case AUDIO_ES:
        SetWLE( &p_buffer[index], p_oggds_header->header.audio.i_channels );
        SetWLE( &p_buffer[index+2], p_oggds_header->header.audio.i_block_align );
        SetDWLE( &p_buffer[index+4], p_oggds_header->header.audio.i_avgbytespersec );
        break;
    }
    index += 8;
    SetDWLE( &p_buffer[index], p_oggds_header->i_padding_1 );
    index += 4;

    /* extra header */
    if( p_oggds_header->i_size > 0 )
    {
        memcpy( &p_buffer[index], (uint8_t *) p_oggds_header + sizeof(*p_oggds_header), p_oggds_header->i_size );
        index += p_oggds_header->i_size;
    }

    SetDWLE( p_isize, index-1 );
    return index;
}