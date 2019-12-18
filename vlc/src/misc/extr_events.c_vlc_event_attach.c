#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t vlc_event_type_t ;
struct TYPE_7__ {int /*<<< orphan*/  lock; TYPE_2__* events; } ;
typedef  TYPE_1__ vlc_event_manager_t ;
struct TYPE_8__ {int /*<<< orphan*/  listeners; } ;
typedef  TYPE_2__ vlc_event_listeners_group_t ;
struct TYPE_9__ {int /*<<< orphan*/  pf_callback; void* p_user_data; } ;
typedef  TYPE_3__ vlc_event_listener_t ;
typedef  int /*<<< orphan*/  vlc_event_callback_t ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_APPEND (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int VLC_ENOMEM ; 
 int VLC_SUCCESS ; 
 TYPE_3__* malloc (int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int vlc_event_attach( vlc_event_manager_t * p_em,
                      vlc_event_type_t event_type,
                      vlc_event_callback_t pf_callback,
                      void *p_user_data )
{
    vlc_event_listener_t * listener;
    vlc_event_listeners_group_t *slot = &p_em->events[event_type];

    listener = malloc(sizeof(vlc_event_listener_t));
    if( !listener )
        return VLC_ENOMEM;

    listener->p_user_data = p_user_data;
    listener->pf_callback = pf_callback;

    vlc_mutex_lock( &p_em->lock );
    ARRAY_APPEND( slot->listeners, listener );
    vlc_mutex_unlock( &p_em->lock );
    return VLC_SUCCESS;
}