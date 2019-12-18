#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * thread; int /*<<< orphan*/  marked_as_waiting; int /*<<< orphan*/ * mutex; int /*<<< orphan*/ * cond; TYPE_2__* tp; } ;
typedef  TYPE_1__ opj_worker_thread_t ;
struct TYPE_6__ {int worker_threads_count; int waiting_worker_thread_count; scalar_t__ state; int /*<<< orphan*/  mutex; int /*<<< orphan*/ * cond; TYPE_1__* worker_threads; } ;
typedef  TYPE_2__ opj_thread_pool_t ;
typedef  int /*<<< orphan*/  OPJ_BOOL ;

/* Variables and functions */
 scalar_t__ OPJWTS_ERROR ; 
 int /*<<< orphan*/  OPJ_FALSE ; 
 int /*<<< orphan*/  OPJ_TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ opj_calloc (size_t,int) ; 
 void* opj_cond_create () ; 
 int /*<<< orphan*/  opj_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opj_mutex_create () ; 
 int /*<<< orphan*/  opj_mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_mutex_lock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opj_mutex_unlock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * opj_thread_create (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  opj_worker_thread_function ; 

__attribute__((used)) static OPJ_BOOL opj_thread_pool_setup(opj_thread_pool_t* tp, int num_threads)
{
    int i;
    OPJ_BOOL bRet = OPJ_TRUE;

    assert(num_threads > 0);

    tp->cond = opj_cond_create();
    if (tp->cond == NULL) {
        return OPJ_FALSE;
    }

    tp->worker_threads = (opj_worker_thread_t*) opj_calloc((size_t)num_threads,
                         sizeof(opj_worker_thread_t));
    if (tp->worker_threads == NULL) {
        return OPJ_FALSE;
    }
    tp->worker_threads_count = num_threads;

    for (i = 0; i < num_threads; i++) {
        tp->worker_threads[i].tp = tp;

        tp->worker_threads[i].mutex = opj_mutex_create();
        if (tp->worker_threads[i].mutex == NULL) {
            tp->worker_threads_count = i;
            bRet = OPJ_FALSE;
            break;
        }

        tp->worker_threads[i].cond = opj_cond_create();
        if (tp->worker_threads[i].cond == NULL) {
            opj_mutex_destroy(tp->worker_threads[i].mutex);
            tp->worker_threads_count = i;
            bRet = OPJ_FALSE;
            break;
        }

        tp->worker_threads[i].marked_as_waiting = OPJ_FALSE;

        tp->worker_threads[i].thread = opj_thread_create(opj_worker_thread_function,
                                       &(tp->worker_threads[i]));
        if (tp->worker_threads[i].thread == NULL) {
            tp->worker_threads_count = i;
            bRet = OPJ_FALSE;
            break;
        }
    }

    /* Wait all threads to be started */
    /* printf("waiting for all threads to be started\n"); */
    opj_mutex_lock(tp->mutex);
    while (tp->waiting_worker_thread_count < num_threads) {
        opj_cond_wait(tp->cond, tp->mutex);
    }
    opj_mutex_unlock(tp->mutex);
    /* printf("all threads started\n"); */

    if (tp->state == OPJWTS_ERROR) {
        bRet = OPJ_FALSE;
    }

    return bRet;
}