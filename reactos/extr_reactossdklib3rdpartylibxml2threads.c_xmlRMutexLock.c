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
typedef  int /*<<< orphan*/ * xmlRMutexPtr ;

/* Variables and functions */

void
xmlRMutexLock(xmlRMutexPtr tok)
{
    if (tok == NULL)
        return;
#ifdef HAVE_PTHREAD_H
    if (libxml_is_threaded == 0)
        return;

    pthread_mutex_lock(&tok->lock);
    if (tok->held) {
        if (pthread_equal(tok->tid, pthread_self())) {
            tok->held++;
            pthread_mutex_unlock(&tok->lock);
            return;
        } else {
            tok->waiters++;
            while (tok->held)
                pthread_cond_wait(&tok->cv, &tok->lock);
            tok->waiters--;
        }
    }
    tok->tid = pthread_self();
    tok->held = 1;
    pthread_mutex_unlock(&tok->lock);
#elif defined HAVE_WIN32_THREADS
    EnterCriticalSection(&tok->cs);
    tok->count++;
#elif defined HAVE_BEOS_THREADS
    if (tok->lock->tid == find_thread(NULL)) {
        tok->count++;
        return;
    } else {
        xmlMutexLock(tok->lock);
        tok->count = 1;
    }
#endif
}