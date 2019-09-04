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
xmlInitThreads(void)
{
#ifdef HAVE_PTHREAD_H
#ifdef XML_PTHREAD_WEAK
    if (libxml_is_threaded == -1) {
        if ((pthread_once != NULL) &&
            (pthread_getspecific != NULL) &&
            (pthread_setspecific != NULL) &&
            (pthread_key_create != NULL) &&
            (pthread_key_delete != NULL) &&
            (pthread_mutex_init != NULL) &&
            (pthread_mutex_destroy != NULL) &&
            (pthread_mutex_lock != NULL) &&
            (pthread_mutex_unlock != NULL) &&
            (pthread_cond_init != NULL) &&
            (pthread_cond_destroy != NULL) &&
            (pthread_cond_wait != NULL) &&
            (pthread_equal != NULL) &&
            (pthread_self != NULL) &&
            (pthread_cond_signal != NULL)) {
            libxml_is_threaded = 1;

/* fprintf(stderr, "Running multithreaded\n"); */
        } else {

/* fprintf(stderr, "Running without multithread\n"); */
            libxml_is_threaded = 0;
        }
    }
#endif /* XML_PTHREAD_WEAK */
#elif defined(HAVE_WIN32_THREADS) && !defined(HAVE_COMPILER_TLS) && (!defined(LIBXML_STATIC) || defined(LIBXML_STATIC_FOR_DLL))
    InitializeCriticalSection(&cleanup_helpers_cs);
#endif
}