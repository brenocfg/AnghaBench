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
 int EOVERFLOW ; 
 int /*<<< orphan*/  VLC_THREAD_ASSERT (char*) ; 
 int errno ; 
 scalar_t__ likely (int) ; 
 scalar_t__ sem_post (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

int vlc_sem_post (vlc_sem_t *sem)
{
    int val;

    if (likely(sem_post (sem) == 0))
        return 0;

    val = errno;

    if (unlikely(val != EOVERFLOW))
        VLC_THREAD_ASSERT ("unlocking semaphore");
    return val;
}