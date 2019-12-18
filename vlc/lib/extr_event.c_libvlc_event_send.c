#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ type; int /*<<< orphan*/  p_obj; } ;
typedef  TYPE_1__ libvlc_event_t ;
struct TYPE_9__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  listeners; int /*<<< orphan*/  p_obj; } ;
typedef  TYPE_2__ libvlc_event_manager_t ;
struct TYPE_10__ {scalar_t__ event_type; int /*<<< orphan*/  p_user_data; int /*<<< orphan*/  (* pf_callback ) (TYPE_1__*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_3__ libvlc_event_listener_t ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ ) ; 
 size_t vlc_array_count (int /*<<< orphan*/ *) ; 
 TYPE_3__* vlc_array_item_at_index (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void libvlc_event_send( libvlc_event_manager_t * p_em,
                        libvlc_event_t * p_event )
{
    /* Fill event with the sending object now */
    p_event->p_obj = p_em->p_obj;

    vlc_mutex_lock(&p_em->lock);
    for (size_t i = 0; i < vlc_array_count(&p_em->listeners); i++)
    {
        libvlc_event_listener_t *listener;

        listener = vlc_array_item_at_index(&p_em->listeners, i);
        if (listener->event_type == p_event->type)
            listener->pf_callback(p_event, listener->p_user_data);
    }
    vlc_mutex_unlock(&p_em->lock);
}