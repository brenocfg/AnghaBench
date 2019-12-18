#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {int /*<<< orphan*/  s; TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_6__ {scalar_t__ i_total_length; scalar_t__ i_input_position; int /*<<< orphan*/  oy; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ __MIN (scalar_t__,int /*<<< orphan*/ ) ; 
 char* ogg_sync_buffer (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ogg_sync_wrote (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  seek_byte (TYPE_1__*,scalar_t__) ; 
 scalar_t__ vlc_stream_Read (int /*<<< orphan*/ ,char*,scalar_t__) ; 

__attribute__((used)) static int64_t get_data( demux_t *p_demux, int64_t i_bytes_to_read )
{
    demux_sys_t *p_sys  = p_demux->p_sys;

    char *buf;
    int64_t i_result;

    if ( p_sys->i_total_length > 0 )
    {
        if ( p_sys->i_input_position + i_bytes_to_read > p_sys->i_total_length )
        {
            i_bytes_to_read = p_sys->i_total_length - p_sys->i_input_position;
            if ( i_bytes_to_read <= 0 ) {
                return 0;
            }
        }
    }

    i_bytes_to_read = __MIN( i_bytes_to_read, INT_MAX );

    seek_byte ( p_demux, p_sys->i_input_position );

    buf = ogg_sync_buffer( &p_sys->oy, i_bytes_to_read );

    i_result = vlc_stream_Read( p_demux->s, buf, i_bytes_to_read );

    ogg_sync_wrote( &p_sys->oy, i_result );
    return i_result;
}