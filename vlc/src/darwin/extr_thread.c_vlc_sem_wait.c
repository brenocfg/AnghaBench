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
 int EINVAL ; 
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  VLC_THREAD_ASSERT (char*) ; 
 scalar_t__ likely (int) ; 
 scalar_t__ semaphore_wait (int /*<<< orphan*/ ) ; 

void vlc_sem_wait (vlc_sem_t *sem)
{
    int val;

    if (likely(semaphore_wait(*sem) == KERN_SUCCESS))
        return;

    val = EINVAL;

    VLC_THREAD_ASSERT ("locking semaphore");
}