#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ libvlc_event_type_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  listeners; } ;
typedef  TYPE_1__ libvlc_event_manager_t ;
struct TYPE_7__ {scalar_t__ event_type; scalar_t__ pf_callback; void* p_user_data; } ;
typedef  TYPE_2__ libvlc_event_listener_t ;
typedef  scalar_t__ libvlc_callback_t ;

/* Variables and functions */
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 size_t vlc_array_count (int /*<<< orphan*/ *) ; 
 TYPE_2__* vlc_array_item_at_index (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vlc_array_remove (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

void libvlc_event_detach(libvlc_event_manager_t *em, libvlc_event_type_t type,
                         libvlc_callback_t callback, void *opaque)
{
    vlc_mutex_lock(&em->lock);
    for (size_t i = 0; i < vlc_array_count(&em->listeners); i++)
    {
         libvlc_event_listener_t *listener;

         listener = vlc_array_item_at_index(&em->listeners, i);

         if (listener->event_type == type
          && listener->pf_callback == callback
          && listener->p_user_data == opaque)
         {   /* that's our listener */
             vlc_array_remove(&em->listeners, i);
             vlc_mutex_unlock(&em->lock);
             free(listener);
             return;
         }
    }
    abort();
}