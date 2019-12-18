#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int worker_threads_count; int /*<<< orphan*/  tls; int /*<<< orphan*/  mutex; scalar_t__ cond; struct TYPE_6__* waiting_worker_thread_list; struct TYPE_6__* next; struct TYPE_6__* worker_threads; int /*<<< orphan*/  thread; int /*<<< orphan*/  state; } ;
typedef  TYPE_1__ opj_worker_thread_list_t ;
typedef  TYPE_1__ opj_thread_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  OPJWTS_STOP ; 
 int /*<<< orphan*/  opj_cond_destroy (scalar_t__) ; 
 int /*<<< orphan*/  opj_cond_signal (scalar_t__) ; 
 int /*<<< orphan*/  opj_free (TYPE_1__*) ; 
 int /*<<< orphan*/  opj_mutex_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_thread_join (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_thread_pool_wait_completion (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_tls_destroy (int /*<<< orphan*/ ) ; 

void opj_thread_pool_destroy(opj_thread_pool_t* tp)
{
    if (!tp) {
        return;
    }
    if (tp->cond) {
        int i;
        opj_thread_pool_wait_completion(tp, 0);

        opj_mutex_lock(tp->mutex);
        tp->state = OPJWTS_STOP;
        opj_mutex_unlock(tp->mutex);

        for (i = 0; i < tp->worker_threads_count; i++) {
            opj_mutex_lock(tp->worker_threads[i].mutex);
            opj_cond_signal(tp->worker_threads[i].cond);
            opj_mutex_unlock(tp->worker_threads[i].mutex);
            opj_thread_join(tp->worker_threads[i].thread);
            opj_cond_destroy(tp->worker_threads[i].cond);
            opj_mutex_destroy(tp->worker_threads[i].mutex);
        }

        opj_free(tp->worker_threads);

        while (tp->waiting_worker_thread_list != NULL) {
            opj_worker_thread_list_t* next = tp->waiting_worker_thread_list->next;
            opj_free(tp->waiting_worker_thread_list);
            tp->waiting_worker_thread_list = next;
        }

        opj_cond_destroy(tp->cond);
    }
    opj_mutex_destroy(tp->mutex);
    opj_tls_destroy(tp->tls);
    opj_free(tp);
}