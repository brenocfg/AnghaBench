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

int
xmlGetThreadId(void)
{
#ifdef HAVE_PTHREAD_H
    pthread_t id;
    int ret;

    if (libxml_is_threaded == 0)
        return (0);
    id = pthread_self();
    /* horrible but preserves compat, see warning above */
    memcpy(&ret, &id, sizeof(ret));
    return (ret);
#elif defined HAVE_WIN32_THREADS
    return GetCurrentThreadId();
#elif defined HAVE_BEOS_THREADS
    return find_thread(NULL);
#else
    return ((int) 0);
#endif
}