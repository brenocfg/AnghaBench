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

/* Variables and functions */

void
__xmlGlobalInitMutexUnlock(void)
{
#ifdef HAVE_PTHREAD_H
#ifdef XML_PTHREAD_WEAK
    if (pthread_mutex_unlock == NULL)
        return;
#endif /* XML_PTHREAD_WEAK */
    pthread_mutex_unlock(&global_init_lock);
#elif defined HAVE_WIN32_THREADS
    if (global_init_lock != NULL) {
	LeaveCriticalSection(global_init_lock);
    }
#elif defined HAVE_BEOS_THREADS
    release_sem(global_init_lock);
#endif
}