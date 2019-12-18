#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlRMutexPtr ;
struct TYPE_8__ {scalar_t__ tid; } ;
struct TYPE_7__ {int held; int count; TYPE_3__* lock; int /*<<< orphan*/  cs; int /*<<< orphan*/  tid; int /*<<< orphan*/  waiters; int /*<<< orphan*/  cv; } ;

/* Variables and functions */
 int /*<<< orphan*/  EnterCriticalSection (int /*<<< orphan*/ *) ; 
 scalar_t__ find_thread (int /*<<< orphan*/ *) ; 
 scalar_t__ libxml_is_threaded ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,TYPE_3__**) ; 
 scalar_t__ pthread_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (TYPE_3__**) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (TYPE_3__**) ; 
 int /*<<< orphan*/  pthread_self () ; 
 int /*<<< orphan*/  xmlMutexLock (TYPE_3__*) ; 

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