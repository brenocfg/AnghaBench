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
struct TYPE_5__ {int i_epg; int /*<<< orphan*/  lock; TYPE_1__** pp_epg; TYPE_1__* p_epg_table; } ;
typedef  TYPE_2__ input_item_t ;
struct TYPE_4__ {int i_source_id; scalar_t__ b_present; } ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void input_item_ChangeEPGSource( input_item_t *p_item, int i_source_id )
{
    vlc_mutex_lock( &p_item->lock );
    p_item->p_epg_table = NULL;
    if( i_source_id > 0 )
    {
        /* Update pointer to current/next table in the full schedule */
        for( int i = 0; i < p_item->i_epg; i++ )
        {
            if( p_item->pp_epg[i]->i_source_id == i_source_id &&
                p_item->pp_epg[i]->b_present )
            {
                p_item->p_epg_table = p_item->pp_epg[i];
                break;
            }
        }
    }
    vlc_mutex_unlock( &p_item->lock );
}