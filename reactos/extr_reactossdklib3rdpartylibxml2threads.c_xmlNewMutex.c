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
typedef  int /*<<< orphan*/ * xmlMutexPtr ;
typedef  int /*<<< orphan*/  xmlMutex ;

/* Variables and functions */
 int /*<<< orphan*/ * malloc (int) ; 

xmlMutexPtr
xmlNewMutex(void)
{
    xmlMutexPtr tok;

    if ((tok = malloc(sizeof(xmlMutex))) == NULL)
        return (NULL);
#ifdef HAVE_PTHREAD_H
    if (libxml_is_threaded != 0)
        pthread_mutex_init(&tok->lock, NULL);
#elif defined HAVE_WIN32_THREADS
    tok->mutex = CreateMutex(NULL, FALSE, NULL);
#elif defined HAVE_BEOS_THREADS
    if ((tok->sem = create_sem(1, "xmlMutex")) < B_OK) {
        free(tok);
        return NULL;
    }
    tok->tid = -1;
#endif
    return (tok);
}