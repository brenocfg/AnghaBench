#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int i_description_items; int /*<<< orphan*/  i_rating; TYPE_5__* description_items; void* psz_short_description; void* psz_name; void* psz_description; int /*<<< orphan*/  i_duration; int /*<<< orphan*/  i_start; int /*<<< orphan*/  i_id; } ;
typedef  TYPE_1__ vlc_epg_event_t ;
struct TYPE_8__ {void* psz_value; void* psz_key; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 scalar_t__ likely (TYPE_1__*) ; 
 TYPE_5__* malloc (int) ; 
 void* strdup (void*) ; 
 TYPE_1__* vlc_epg_event_New (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

vlc_epg_event_t * vlc_epg_event_Duplicate( const vlc_epg_event_t *p_src )
{
    vlc_epg_event_t *p_evt = vlc_epg_event_New( p_src->i_id, p_src->i_start,
                                                p_src->i_duration );
    if( likely(p_evt) )
    {
        if( p_src->psz_description )
            p_evt->psz_description = strdup( p_src->psz_description );
        if( p_src->psz_name )
            p_evt->psz_name = strdup( p_src->psz_name );
        if( p_src->psz_short_description )
            p_evt->psz_short_description = strdup( p_src->psz_short_description );
        if( p_src->i_description_items )
        {
            p_evt->description_items = malloc( sizeof(*p_evt->description_items) *
                                               p_src->i_description_items );
            if( p_evt->description_items )
            {
                for( int i=0; i<p_src->i_description_items; i++ )
                {
                    p_evt->description_items[i].psz_key =
                            strdup( p_src->description_items[i].psz_key );
                    p_evt->description_items[i].psz_value =
                            strdup( p_src->description_items[i].psz_value );
                    if(!p_evt->description_items[i].psz_value ||
                       !p_evt->description_items[i].psz_key)
                    {
                        free(p_evt->description_items[i].psz_key);
                        free(p_evt->description_items[i].psz_value);
                        break;
                    }
                    p_evt->i_description_items++;
                }
            }
        }
        p_evt->i_rating = p_src->i_rating;
    }
    return p_evt;
}