#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  libvlc_event_type_t ;
struct TYPE_7__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  listeners; } ;
typedef  TYPE_1__ libvlc_event_manager_t ;
struct TYPE_8__ {int /*<<< orphan*/  pf_callback; void* p_user_data; int /*<<< orphan*/  event_type; } ;
typedef  TYPE_2__ libvlc_event_listener_t ;
typedef  int /*<<< orphan*/  libvlc_callback_t ;

/* Variables and functions */
 int ENOMEM ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 TYPE_2__* malloc (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_array_append (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

int libvlc_event_attach(libvlc_event_manager_t *em, libvlc_event_type_t type,
                        libvlc_callback_t callback, void *opaque)
{
    libvlc_event_listener_t *listener = malloc(sizeof (*listener));
    if (unlikely(listener == NULL))
        return ENOMEM;

    listener->event_type = type;
    listener->p_user_data = opaque;
    listener->pf_callback = callback;

    int i_ret;
    vlc_mutex_lock(&em->lock);
    if(vlc_array_append(&em->listeners, listener) != 0)
    {
        i_ret = VLC_EGENERIC;
        free(listener);
    }
    else
        i_ret = VLC_SUCCESS;
    vlc_mutex_unlock(&em->lock);
    return i_ret;
}