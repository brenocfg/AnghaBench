#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int i_event; TYPE_2__** pp_event; TYPE_2__* p_current; } ;
typedef  TYPE_1__ vlc_epg_t ;
struct TYPE_11__ {scalar_t__ i_start; } ;
typedef  TYPE_2__ vlc_epg_event_t ;
typedef  int ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  TAB_APPEND (int,TYPE_2__**,TYPE_2__*) ; 
 int /*<<< orphan*/  TAB_INSERT (int,TYPE_2__**,TYPE_2__*,int) ; 
 int /*<<< orphan*/  vlc_epg_event_Delete (TYPE_2__*) ; 

bool vlc_epg_AddEvent( vlc_epg_t *p_epg, vlc_epg_event_t *p_evt )
{
    ssize_t i_pos = -1;

    /* Insertions are supposed in sequential order first */
    if( p_epg->i_event )
    {
        if( p_epg->pp_event[0]->i_start > p_evt->i_start )
        {
            i_pos = 0;
        }
        else if ( p_epg->pp_event[p_epg->i_event - 1]->i_start >= p_evt->i_start )
        {
            /* Do bisect search lower start time entry */
            size_t i_lower = 0;
            size_t i_upper = p_epg->i_event - 1;

            while( i_lower < i_upper )
            {
                size_t i_split = ( i_lower + i_upper ) / 2;
                vlc_epg_event_t *p_cur = p_epg->pp_event[i_split];

                if( p_cur->i_start < p_evt->i_start )
                {
                    i_lower = i_split + 1;
                }
                else if ( p_cur->i_start >= p_evt->i_start )
                {
                    i_upper = i_split;
                }
            }
            i_pos = i_lower;
        }
    }

    if( i_pos != -1 )
    {
        /* There can be only one event at same time */
        if( p_epg->pp_event[i_pos]->i_start == p_evt->i_start )
        {
            vlc_epg_event_Delete( p_epg->pp_event[i_pos] );
            if( p_epg->p_current == p_epg->pp_event[i_pos] )
                p_epg->p_current = p_evt;
            p_epg->pp_event[i_pos] = p_evt;
            return true;
        }
        else
        {
            TAB_INSERT( p_epg->i_event, p_epg->pp_event, p_evt, i_pos );
        }
    }
    else
        TAB_APPEND( p_epg->i_event, p_epg->pp_event, p_evt );

    return true;
}