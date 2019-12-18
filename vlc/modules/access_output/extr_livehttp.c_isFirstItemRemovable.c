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
typedef  scalar_t__ vlc_tick_t ;
typedef  unsigned int uint32_t ;
struct TYPE_5__ {unsigned int i_segment; int i_numsegs; int segment_max_length; int /*<<< orphan*/  segments_t; } ;
typedef  TYPE_1__ sout_access_out_sys_t ;
struct TYPE_6__ {scalar_t__ segment_length; } ;
typedef  TYPE_2__ output_segment_t ;

/* Variables and functions */
 TYPE_2__* vlc_array_item_at_index (int /*<<< orphan*/ *,unsigned int) ; 

__attribute__((used)) static bool isFirstItemRemovable( sout_access_out_sys_t *p_sys, uint32_t i_firstseg, uint32_t i_index_offset )
{
    vlc_tick_t duration = 0;

    /* Check that segment has been out of playlist for segment_length + (p_sys->i_numsegs * p_sys->segment_max_length) amount
     * We check this by calculating duration of the items that replaced first item in playlist
     */
    for( unsigned int index = 0; index < i_index_offset; index++ )
    {
        output_segment_t *segment = vlc_array_item_at_index( &p_sys->segments_t, p_sys->i_segment - i_firstseg + index );
        duration += segment->segment_length;
    }
    output_segment_t *first = vlc_array_item_at_index( &p_sys->segments_t, 0 );

    return duration >= (first->segment_length + (p_sys->i_numsegs * p_sys->segment_max_length));
}