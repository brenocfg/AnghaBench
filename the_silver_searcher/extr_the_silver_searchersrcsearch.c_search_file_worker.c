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
struct TYPE_5__ {struct TYPE_5__* path; struct TYPE_5__* next; } ;
typedef  TYPE_1__ work_queue_t ;

/* Variables and functions */
 scalar_t__ TRUE ; 
 scalar_t__ done_adding_files ; 
 int /*<<< orphan*/  files_ready ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (char*,int) ; 
 int /*<<< orphan*/  pthread_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  search_file (TYPE_1__*) ; 
 TYPE_1__* work_queue ; 
 int /*<<< orphan*/  work_queue_mtx ; 
 int /*<<< orphan*/ * work_queue_tail ; 

void *search_file_worker(void *i) {
    work_queue_t *queue_item;
    int worker_id = *(int *)i;

    log_debug("Worker %i started", worker_id);
    while (TRUE) {
        pthread_mutex_lock(&work_queue_mtx);
        while (work_queue == NULL) {
            if (done_adding_files) {
                pthread_mutex_unlock(&work_queue_mtx);
                log_debug("Worker %i finished.", worker_id);
                pthread_exit(NULL);
            }
            pthread_cond_wait(&files_ready, &work_queue_mtx);
        }
        queue_item = work_queue;
        work_queue = work_queue->next;
        if (work_queue == NULL) {
            work_queue_tail = NULL;
        }
        pthread_mutex_unlock(&work_queue_mtx);

        search_file(queue_item->path);
        free(queue_item->path);
        free(queue_item);
    }
}