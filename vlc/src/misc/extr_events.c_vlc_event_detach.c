#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  size_t vlc_event_type_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; TYPE_2__* events; } ;
typedef  TYPE_1__ vlc_event_manager_t ;
struct TYPE_7__ {int i_size; struct vlc_event_listener_t** p_elems; } ;
struct TYPE_6__ {TYPE_4__ listeners; } ;
typedef  TYPE_2__ vlc_event_listeners_group_t ;
typedef  scalar_t__ vlc_event_callback_t ;
struct vlc_event_listener_t {scalar_t__ pf_callback; void* p_user_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_REMOVE (TYPE_4__,int) ; 
 int /*<<< orphan*/  free (struct vlc_event_listener_t*) ; 
 int /*<<< orphan*/  vlc_assert_unreachable () ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void vlc_event_detach( vlc_event_manager_t *p_em,
                       vlc_event_type_t event_type,
                       vlc_event_callback_t pf_callback,
                       void *p_user_data )
{
    vlc_event_listeners_group_t *slot = &p_em->events[event_type];

    vlc_mutex_lock( &p_em->lock );

    for (int i = 0; i < slot->listeners.i_size; ++i)
    {
        struct vlc_event_listener_t *listener = slot->listeners.p_elems[i];
        if( listener->pf_callback == pf_callback &&
            listener->p_user_data == p_user_data )
        {
            /* that's our listener */
            ARRAY_REMOVE( slot->listeners, i );
            vlc_mutex_unlock( &p_em->lock );
            free( listener );
            return;
        }
    }

    vlc_assert_unreachable();
}