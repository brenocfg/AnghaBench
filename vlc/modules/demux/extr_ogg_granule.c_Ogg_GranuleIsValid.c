#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int i_first_frame_index; int /*<<< orphan*/  b_oggds; } ;
typedef  TYPE_1__ logical_stream_t ;
typedef  int int64_t ;

/* Variables and functions */

bool Ogg_GranuleIsValid( const logical_stream_t *p_stream, int64_t i_granule )
{
    /* First frame in ogm is 0 (0[header] 0[frame] -1 2 3 -1 5 ...) */
    return !( i_granule < p_stream->i_first_frame_index - !!p_stream->b_oggds );
}