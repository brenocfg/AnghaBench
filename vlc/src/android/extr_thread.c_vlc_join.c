#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* vlc_thread_t ;
struct TYPE_4__ {int /*<<< orphan*/  thread; int /*<<< orphan*/  finished; } ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_THREAD_ASSERT (char*) ; 
 int /*<<< orphan*/  clean_detached_thread (TYPE_1__*) ; 
 int pthread_join (int /*<<< orphan*/ ,void**) ; 
 int /*<<< orphan*/  vlc_sem_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_wait (int /*<<< orphan*/ *) ; 

void vlc_join (vlc_thread_t handle, void **result)
{
    vlc_sem_wait (&handle->finished);
    vlc_sem_destroy (&handle->finished);

    int val = pthread_join (handle->thread, result);
    VLC_THREAD_ASSERT ("joining thread");
    clean_detached_thread(handle);
}