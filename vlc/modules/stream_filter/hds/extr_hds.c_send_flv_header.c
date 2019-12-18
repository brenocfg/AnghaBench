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
typedef  scalar_t__ uint32_t ;
struct TYPE_4__ {scalar_t__ flv_header; scalar_t__ flv_header_len; scalar_t__ flv_header_bytes_sent; } ;
typedef  TYPE_1__ stream_sys_t ;
typedef  int /*<<< orphan*/  hds_stream_t ;

/* Variables and functions */
 int /*<<< orphan*/  initialize_header_and_metadata (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (void*,scalar_t__,scalar_t__) ; 

__attribute__((used)) static int send_flv_header( hds_stream_t *stream, stream_sys_t* p_sys,
                            void* buffer, unsigned i_read )
{
    if ( !p_sys->flv_header )
    {
        initialize_header_and_metadata( p_sys, stream );
    }

    uint32_t to_be_read = i_read;
    uint32_t header_remaining =
        p_sys->flv_header_len - p_sys->flv_header_bytes_sent;
    if( to_be_read > header_remaining ) {
        to_be_read = header_remaining;
    }

    memcpy( buffer, p_sys->flv_header + p_sys->flv_header_bytes_sent, to_be_read );

    p_sys->flv_header_bytes_sent += to_be_read;
    return to_be_read;
}