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
__xmlGlobalInitMutexLock(void)
{
    /* Make sure the global init lock is initialized and then lock it. */
#ifdef HAVE_PTHREAD_H
    /* The mutex is statically initialized, so we just lock it. */
#ifdef XML_PTHREAD_WEAK
    if (pthread_mutex_lock == NULL)
        return;
#endif /* XML_PTHREAD_WEAK */
    pthread_mutex_lock(&global_init_lock);
#elif defined HAVE_WIN32_THREADS
    LPCRITICAL_SECTION cs;

    /* Create a new critical section */
    if (global_init_lock == NULL) {
        cs = malloc(sizeof(CRITICAL_SECTION));
        if (cs == NULL) {
            xmlGenericError(xmlGenericErrorContext,
                            "xmlGlobalInitMutexLock: out of memory\n");
            return;
        }
        InitializeCriticalSection(cs);

        /* Swap it into the global_init_lock */
#ifdef InterlockedCompareExchangePointer
        InterlockedCompareExchangePointer((void **) &global_init_lock,
                                          cs, NULL);
#else /* Use older void* version */
        InterlockedCompareExchange((void **) &global_init_lock,
                                   (void *) cs, NULL);
#endif /* InterlockedCompareExchangePointer */

        /* If another thread successfully recorded its critical
         * section in the global_init_lock then discard the one
         * allocated by this thread. */
        if (global_init_lock != cs) {
            DeleteCriticalSection(cs);
            free(cs);
        }
    }

    /* Lock the chosen critical section */
    EnterCriticalSection(global_init_lock);
#elif defined HAVE_BEOS_THREADS
    int32 sem;

    /* Allocate a new semaphore */
    sem = create_sem(1, "xmlGlobalinitMutex");

    while (global_init_lock == -1) {
        if (atomic_add(&global_init_count, 1) == 0) {
            global_init_lock = sem;
        } else {
            snooze(1);
            atomic_add(&global_init_count, -1);
        }
    }

    /* If another thread successfully recorded its critical
     * section in the global_init_lock then discard the one
     * allocated by this thread. */
    if (global_init_lock != sem)
        delete_sem(sem);

    /* Acquire the chosen semaphore */
    if (acquire_sem(global_init_lock) != B_NO_ERROR) {
#ifdef DEBUG_THREADS
        xmlGenericError(xmlGenericErrorContext,
                        "xmlGlobalInitMutexLock():BeOS:Couldn't acquire semaphore\n");
#endif
    }
#endif
}