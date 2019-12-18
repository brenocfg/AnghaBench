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
struct TYPE_3__ {int /*<<< orphan*/  tid; int /*<<< orphan*/  sem; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ B_NO_ERROR ; 
 int /*<<< orphan*/  INFINITE ; 
 int /*<<< orphan*/  WaitForSingleObject (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ acquire_sem (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  find_thread (int /*<<< orphan*/ *) ; 
 scalar_t__ libxml_is_threaded ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xmlGenericError (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  xmlGenericErrorContext ; 

void
xmlMutexLock(xmlMutexPtr tok)
{
    if (tok == NULL)
        return;
#ifdef HAVE_PTHREAD_H
    if (libxml_is_threaded != 0)
        pthread_mutex_lock(&tok->lock);
#elif defined HAVE_WIN32_THREADS
    WaitForSingleObject(tok->mutex, INFINITE);
#elif defined HAVE_BEOS_THREADS
    if (acquire_sem(tok->sem) != B_NO_ERROR) {
#ifdef DEBUG_THREADS
        xmlGenericError(xmlGenericErrorContext,
                        "xmlMutexLock():BeOS:Couldn't aquire semaphore\n");
#endif
    }
    tok->tid = find_thread(NULL);
#endif

}