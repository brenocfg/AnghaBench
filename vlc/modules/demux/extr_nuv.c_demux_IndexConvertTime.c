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
typedef  scalar_t__ vlc_tick_t ;
typedef  int uint64_t ;
struct TYPE_5__ {int i_idx; TYPE_1__* idx; } ;
typedef  TYPE_2__ demux_index_t ;
struct TYPE_4__ {scalar_t__ i_time; int i_offset; } ;

/* Variables and functions */

__attribute__((used)) static uint64_t demux_IndexConvertTime(demux_index_t *p_idx,
                                       vlc_tick_t i_time)
{
    int i_min = 0;
    int i_max = p_idx->i_idx-1;

    /* Empty index */
    if( p_idx->i_idx <= 0 )
        return -1;

    /* Special border case */
    if( i_time <= p_idx->idx[0].i_time )
        return p_idx->idx[0].i_offset;
    if( i_time >= p_idx->idx[i_max].i_time )
        return p_idx->idx[i_max].i_offset;

    /* Dicho */
    for( ;; )
    {
        int i_med;

        if( i_max - i_min <= 1 )
            break;

        i_med = (i_min+i_max)/2;
        if( p_idx->idx[i_med].i_time < i_time )
            i_min = i_med;
        else if( p_idx->idx[i_med].i_time > i_time )
            i_max = i_med;
        else
            return p_idx->idx[i_med].i_offset;
    }

    /* return nearest in time */
    if( i_time - p_idx->idx[i_min].i_time < p_idx->idx[i_max].i_time - i_time )
        return p_idx->idx[i_min].i_offset;
    else
        return p_idx->idx[i_max].i_offset;
}