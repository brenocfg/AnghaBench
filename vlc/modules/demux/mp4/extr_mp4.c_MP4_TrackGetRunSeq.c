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
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {scalar_t__ i_chunk_count; size_t i_chunk; TYPE_1__* chunk; } ;
typedef  TYPE_2__ mp4_track_t ;
struct TYPE_4__ {int /*<<< orphan*/  i_virtual_run_number; } ;

/* Variables and functions */

__attribute__((used)) static uint32_t MP4_TrackGetRunSeq( mp4_track_t *p_track )
{
    if( p_track->i_chunk_count > 0 )
        return p_track->chunk[p_track->i_chunk].i_virtual_run_number;
    return 0;
}