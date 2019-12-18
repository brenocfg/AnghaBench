#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_sem_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_THREAD_ASSERT (char*) ; 
 int errno ; 
 scalar_t__ likely (int) ; 
 scalar_t__ sem_destroy (int /*<<< orphan*/ *) ; 

void vlc_sem_destroy (vlc_sem_t *sem)
{
    int val;

    if (likely(sem_destroy (sem) == 0))
        return;

    val = errno;

    VLC_THREAD_ASSERT ("destroying semaphore");
}