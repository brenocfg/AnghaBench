#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ogg_packet ;
struct TYPE_10__ {scalar_t__ i_data_start; int /*<<< orphan*/  os; } ;
typedef  TYPE_1__ logical_stream_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_11__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ demux_t ;
struct TYPE_13__ {int fill; scalar_t__ data; } ;
struct TYPE_12__ {scalar_t__ i_input_position; int b_page_waiting; int /*<<< orphan*/  current_page; TYPE_6__ oy; } ;
typedef  TYPE_3__ demux_sys_t ;

/* Variables and functions */
 scalar_t__ OGGSEEK_BYTES_TO_READ ; 
 scalar_t__ get_data (TYPE_2__*,scalar_t__) ; 
 scalar_t__ ogg_page_granulepos (int /*<<< orphan*/ *) ; 
 scalar_t__ ogg_stream_packetout (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ ogg_stream_pagein (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ogg_stream_reset (int /*<<< orphan*/ *) ; 
 scalar_t__ ogg_sync_pageseek (TYPE_6__*,int /*<<< orphan*/ *) ; 
 scalar_t__ oggseek_read_page (TYPE_2__*) ; 
 int /*<<< orphan*/  seek_byte (TYPE_2__*,scalar_t__) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int) ; 

__attribute__((used)) static int64_t find_first_page_granule( demux_t *p_demux,
                                int64_t i_pos1, int64_t i_pos2,
                                logical_stream_t *p_stream,
                                int64_t *i_granulepos )
{
    int64_t i_result;
    *i_granulepos = -1;
    int64_t i_bytes_to_read = i_pos2 - i_pos1 + 1;
    int64_t i_bytes_read;
    int64_t i_packets_checked;

    demux_sys_t *p_sys  = p_demux->p_sys;

    ogg_packet op;

    seek_byte( p_demux, i_pos1 );

    if ( i_pos1 == p_stream->i_data_start )
        return p_sys->i_input_position;

    if ( i_bytes_to_read > OGGSEEK_BYTES_TO_READ ) i_bytes_to_read = OGGSEEK_BYTES_TO_READ;

    while ( 1 )
    {

        if ( p_sys->i_input_position >= i_pos2 )
        {
            /* we reached the end and found no pages */
            return -1;
        }

        /* read next chunk */
        if ( ! ( i_bytes_read = get_data( p_demux, i_bytes_to_read ) ) )
        {
            /* EOF */
            return -1;
        }

        i_bytes_to_read = OGGSEEK_BYTES_TO_READ;

        i_result = ogg_sync_pageseek( &p_sys->oy, &p_sys->current_page );

        if ( i_result < 0 )
        {
            /* found a page, sync to page start */
            p_sys->i_input_position -= i_result;
            i_pos1 = p_sys->i_input_position;
            continue;
        }

        if ( i_result > 0 || ( i_result == 0 && p_sys->oy.fill > 3 &&
                               ! strncmp( (char *)p_sys->oy.data, "OggS" , 4 ) ) )
        {
            i_pos1 = p_sys->i_input_position;
            break;
        }

        p_sys->i_input_position += i_bytes_read;

    };

    seek_byte( p_demux, p_sys->i_input_position );
    ogg_stream_reset( &p_stream->os );

    while( 1 )
    {

        if ( p_sys->i_input_position >= i_pos2 )
        {
            /* reached the end of the search region and nothing was found */
            return p_sys->i_input_position;
        }

        p_sys->b_page_waiting = false;

        if ( ! ( i_result = oggseek_read_page( p_demux ) ) )
        {
            /* EOF */
            return p_sys->i_input_position;
        }

        // found a page
        if ( ogg_stream_pagein( &p_stream->os, &p_sys->current_page ) != 0 )
        {
            /* page is not for this stream or incomplete */
            p_sys->i_input_position += i_result;
            continue;
        }

        if ( ogg_page_granulepos( &p_sys->current_page ) <= 0 )
        {
            /* A negative granulepos means that the packet continues on the
             * next page => read the next page */
            p_sys->i_input_position += i_result;
            continue;
        }

        i_packets_checked = 0;

        while ( ogg_stream_packetout( &p_stream->os, &op ) > 0 )
        {
            i_packets_checked++;
        }

        if ( i_packets_checked )
        {
            *i_granulepos = ogg_page_granulepos( &p_sys->current_page );
            return i_pos1;
        }

        /*  -> start of next page */
        p_sys->i_input_position += i_result;
        i_pos1 = p_sys->i_input_position;
    }
}