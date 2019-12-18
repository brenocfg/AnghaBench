#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
struct TYPE_10__ {scalar_t__ i_new_stop; TYPE_2__* p_source; } ;
typedef  TYPE_3__ subsdelay_heap_entry_t ;
struct TYPE_11__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ filter_t ;
struct TYPE_8__ {int i_count; TYPE_3__** p_list; } ;
struct TYPE_12__ {int i_overlap; scalar_t__ i_min_stops_interval; scalar_t__ i_min_stop_start_interval; scalar_t__ i_min_start_stop_interval; TYPE_1__ heap; } ;
typedef  TYPE_5__ filter_sys_t ;
struct TYPE_9__ {scalar_t__ i_start; } ;

/* Variables and functions */
 int /*<<< orphan*/  SubsdelayEntryNewStopValueUpdated (TYPE_3__*) ; 
 scalar_t__ __MAX (scalar_t__,scalar_t__) ; 
 int __MIN (int,int) ; 

__attribute__((used)) static void SubsdelayEnforceDelayRules( filter_t *p_filter )
{
    subsdelay_heap_entry_t ** p_list;
    int i_count, i_overlap;
    vlc_tick_t i_offset;
    vlc_tick_t i_min_stops_interval;
    vlc_tick_t i_min_stop_start_interval;
    vlc_tick_t i_min_start_stop_interval;

    filter_sys_t *p_sys = p_filter->p_sys;

    p_list = p_sys->heap.p_list;
    i_count = p_sys->heap.i_count;

    i_overlap = p_sys->i_overlap;
    i_min_stops_interval = p_sys->i_min_stops_interval;
    i_min_stop_start_interval = p_sys->i_min_stop_start_interval;
    i_min_start_stop_interval = p_sys->i_min_start_stop_interval;

    /* step 1 - enforce min stops interval rule (extend delays) */

    /* look for:
    [subtitle 1 ..............]
           [subtitle 2 ..............]
                              |<-MinStopsInterval->|

     * and extend newer subtitle:
    [subtitle 1 ..............]
           [subtitle 2 ............................]
                              |<-MinStopsInterval->|
    */

    for( int i = 0; i < i_count - 1; i++ )
    {
        p_list[i + 1]->i_new_stop = __MAX( p_list[i + 1]->i_new_stop,
                p_list[i]->i_new_stop + i_min_stops_interval );
    }

    /* step 2 - enforce min stop start interval rule (extend delays) */

    /* look for:
    [subtitle 1 .........]
                                   [subtitle 2 ....]
          |<-MinStopStartInterval->|

     * and fill the gap:
    [subtitle 1 ..................]
                                   [subtitle 2 ....]
          |<-MinStopStartInterval->|
    */

    for( int i = 0; i < i_count; i++ )
    {
        for( int j = i + 1; j < __MIN( i_count, i + 1 + i_overlap ); j++ )
        {
            i_offset = p_list[j]->p_source->i_start - p_list[i]->i_new_stop;

            if( i_offset <= 0 )
            {
                continue;
            }

            if( i_offset < i_min_stop_start_interval )
            {
                p_list[i]->i_new_stop = p_list[j]->p_source->i_start;
            }

            break;
        }
    }

    /* step 3 - enforce min start stop interval rule (shorten delays) */

    /* look for:
    [subtitle 1 ............]
                    [subtitle 2 ....................]
                    |<-MinStartStopInterval->|

     * and remove the overlapping part:
    [subtitle 1 ...]
                    [subtitle 2 ....................]
                    |<-MinStartStopInterval->|
    */


    for( int i = 0; i < i_count; i++ )
    {
        for( int j = i + 1; j < __MIN( i_count, i + 1 + i_overlap ); j++ )
        {
            i_offset = p_list[i]->i_new_stop - p_list[j]->p_source->i_start;

            if( i_offset <= 0 )
            {
                break;
            }

            if( i_offset < i_min_start_stop_interval )
            {
                p_list[i]->i_new_stop = p_list[j]->p_source->i_start;
                break;
            }
        }
    }

    /* step 4 - enforce max overlapping rule (shorten delays)*/

    /* look for: (overlap = 2)
    [subtitle 1 ..............]
             [subtitle 2 ..............]
                      [subtitle 3 ..............]


     * and cut older subtitle:
    [subtitle 1 .....]
             [subtitle 2 ..............]
                      [subtitle 3 ..............]
    */

    for( int i = 0; i < i_count - i_overlap; i++ )
    {
        p_list[i]->i_new_stop = __MIN(p_list[i]->i_new_stop, p_list[i + i_overlap]->p_source->i_start);
    }

    /* finally - update all */

    for( int i = 0; i < i_count; i++ )
    {
        SubsdelayEntryNewStopValueUpdated( p_list[i] );
    }
}