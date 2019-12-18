#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlMutexPtr ;
struct TYPE_3__ {int tid; int /*<<< orphan*/  sem; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  ReleaseMutex (int /*<<< orphan*/ ) ; 
 int find_thread (int /*<<< orphan*/ *) ; 
 scalar_t__ libxml_is_threaded ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  release_sem (int /*<<< orphan*/ ) ; 

void
xmlMutexUnlock(xmlMutexPtr tok)
{
    if (tok == NULL)
        return;
#ifdef HAVE_PTHREAD_H
    if (libxml_is_threaded != 0)
        pthread_mutex_unlock(&tok->lock);
#elif defined HAVE_WIN32_THREADS
    ReleaseMutex(tok->mutex);
#elif defined HAVE_BEOS_THREADS
    if (tok->tid == find_thread(NULL)) {
        tok->tid = -1;
        release_sem(tok->sem);
    }
#endif
}