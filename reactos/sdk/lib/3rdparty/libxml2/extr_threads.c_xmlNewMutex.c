#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_1__* xmlMutexPtr ;
typedef  int /*<<< orphan*/  xmlMutex ;
struct TYPE_5__ {int tid; int /*<<< orphan*/  sem; int /*<<< orphan*/  mutex; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  B_OK ; 
 int /*<<< orphan*/  CreateMutex (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  create_sem (int,char*) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 scalar_t__ libxml_is_threaded ; 
 TYPE_1__* malloc (int) ; 
 int /*<<< orphan*/  pthread_mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

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