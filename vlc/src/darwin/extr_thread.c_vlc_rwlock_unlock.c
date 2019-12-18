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
typedef  int /*<<< orphan*/  vlc_rwlock_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_THREAD_ASSERT (char*) ; 
 int pthread_rwlock_unlock (int /*<<< orphan*/ *) ; 

void vlc_rwlock_unlock (vlc_rwlock_t *lock)
{
    int val = pthread_rwlock_unlock (lock);
    VLC_THREAD_ASSERT ("releasing R/W lock");
}