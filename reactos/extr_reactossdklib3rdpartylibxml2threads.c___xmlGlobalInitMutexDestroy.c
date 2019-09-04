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
__xmlGlobalInitMutexDestroy(void)
{
#ifdef HAVE_PTHREAD_H
#elif defined HAVE_WIN32_THREADS
    if (global_init_lock != NULL) {
        DeleteCriticalSection(global_init_lock);
        free(global_init_lock);
        global_init_lock = NULL;
    }
#endif
}