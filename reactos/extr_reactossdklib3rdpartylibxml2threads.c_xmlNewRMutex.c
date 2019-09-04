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
typedef  int /*<<< orphan*/  xmlRMutex ;

/* Variables and functions */
 int /*<<< orphan*/ * malloc (int) ; 

xmlRMutexPtr
xmlNewRMutex(void)
{
    xmlRMutexPtr tok;

    if ((tok = malloc(sizeof(xmlRMutex))) == NULL)
        return (NULL);
#ifdef HAVE_PTHREAD_H
    if (libxml_is_threaded != 0) {
        pthread_mutex_init(&tok->lock, NULL);
        tok->held = 0;
        tok->waiters = 0;
        pthread_cond_init(&tok->cv, NULL);
    }
#elif defined HAVE_WIN32_THREADS
    InitializeCriticalSection(&tok->cs);
    tok->count = 0;
#elif defined HAVE_BEOS_THREADS
    if ((tok->lock = xmlNewMutex()) == NULL) {
        free(tok);
        return NULL;
    }
    tok->count = 0;
#endif
    return (tok);
}