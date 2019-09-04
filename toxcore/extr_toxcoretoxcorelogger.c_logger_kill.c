#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  log_file; struct TYPE_4__* msg; struct TYPE_4__* posstr; struct TYPE_4__* tstr; struct TYPE_4__* id; } ;
typedef  TYPE_1__ Logger ;

/* Variables and functions */
 scalar_t__ fclose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  perror (char*) ; 
 int /*<<< orphan*/  pthread_mutex_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ ) ; 

void logger_kill(Logger *log)
{
#ifndef TOX_LOGGER /* Disabled */
    return;
#endif

    if (!log)
        return;

    pthread_mutex_lock(log->mutex);
    free(log->id);
    free(log->tstr);
    free(log->posstr);
    free(log->msg);

    if (fclose(log->log_file) != 0)
        perror("Could not close log file");

    pthread_mutex_unlock(log->mutex);
    pthread_mutex_destroy(log->mutex);

    free(log);
}