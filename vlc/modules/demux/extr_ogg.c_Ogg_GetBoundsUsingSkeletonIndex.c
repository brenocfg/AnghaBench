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
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {TYPE_1__* p_skel; } ;
typedef  TYPE_2__ logical_stream_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_4__ {unsigned char* p_index; scalar_t__ i_indexfirstnum; scalar_t__ i_indexstampden; scalar_t__ i_indexlastnum; int i_index_size; scalar_t__ i_index; } ;

/* Variables and functions */
 unsigned char* Read7BitsVariableLE (unsigned char const*,unsigned char const*,scalar_t__*) ; 
 scalar_t__ VLC_TICK_0 ; 
 scalar_t__ VLC_TICK_INVALID ; 

bool Ogg_GetBoundsUsingSkeletonIndex( logical_stream_t *p_stream, vlc_tick_t i_time,
                                      int64_t *pi_lower, int64_t *pi_upper )
{
    if ( !p_stream || !p_stream->p_skel || !p_stream->p_skel->p_index ||
         i_time == VLC_TICK_INVALID )
        return false;

    i_time -= VLC_TICK_0;

    /* Validate range */
    if ( i_time < p_stream->p_skel->i_indexfirstnum
                * p_stream->p_skel->i_indexstampden ||
         i_time > p_stream->p_skel->i_indexlastnum
                * p_stream->p_skel->i_indexstampden ) return false;

    /* Then Lookup its index */
    unsigned const char *p_fwdbyte = p_stream->p_skel->p_index;
    struct
    {
        int64_t i_pos;
        vlc_tick_t i_time;
    } current = { 0, 0 }, prev = { -1, -1 };

    uint64_t i_keypoints_found = 0;

    while( p_fwdbyte < p_fwdbyte + p_stream->p_skel->i_index_size
           && i_keypoints_found < p_stream->p_skel->i_index )
    {
        uint64_t i_val;
        p_fwdbyte = Read7BitsVariableLE( p_fwdbyte,
                        p_fwdbyte + p_stream->p_skel->i_index_size, &i_val );
        current.i_pos += i_val;
        p_fwdbyte = Read7BitsVariableLE( p_fwdbyte,
                        p_fwdbyte + p_stream->p_skel->i_index_size, &i_val );
        current.i_time += i_val * p_stream->p_skel->i_indexstampden;
        if ( current.i_pos < 0 || current.i_time < 0 ) break;

        i_keypoints_found++;

        if ( i_time <= current.i_time )
        {
            *pi_lower = prev.i_pos;
            *pi_upper = current.i_pos;
            return ( i_time == current.i_time );
        }
        prev = current;
    }
    return false;
}