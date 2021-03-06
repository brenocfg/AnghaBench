#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vlc_threadvar_t ;
struct vlc_thread {int /*<<< orphan*/  cancel_sock; int /*<<< orphan*/  done_event; int /*<<< orphan*/  cancel_event; scalar_t__ detached; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* destroy ) (void*) ;struct TYPE_5__* prev; } ;

/* Variables and functions */
 int /*<<< orphan*/  DosCloseEventSem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (struct vlc_thread*) ; 
 int /*<<< orphan*/  soclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (void*) ; 
 int /*<<< orphan*/  super_mutex ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 void* vlc_threadvar_get (TYPE_1__*) ; 
 TYPE_1__* vlc_threadvar_last ; 
 int /*<<< orphan*/  vlc_threadvar_set (TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlc_thread_cleanup (struct vlc_thread *th)
{
    vlc_threadvar_t key;

retry:
    /* TODO: use RW lock or something similar */
    vlc_mutex_lock (&super_mutex);
    for (key = vlc_threadvar_last; key != NULL; key = key->prev)
    {
        void *value = vlc_threadvar_get (key);
        if (value != NULL && key->destroy != NULL)
        {
            vlc_mutex_unlock (&super_mutex);
            vlc_threadvar_set (key, NULL);
            key->destroy (value);
            goto retry;
        }
    }
    vlc_mutex_unlock (&super_mutex);

    if (th->detached)
    {
        DosCloseEventSem (th->cancel_event);
        DosCloseEventSem (th->done_event );

        soclose (th->cancel_sock);

        free (th);
    }
}