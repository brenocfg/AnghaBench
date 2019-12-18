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
struct TYPE_3__ {int signaling_threshold; int pending_jobs_count; int /*<<< orphan*/ * mutex; int /*<<< orphan*/  cond; } ;
typedef  TYPE_1__ opj_thread_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  opj_cond_wait (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  opj_mutex_unlock (int /*<<< orphan*/ *) ; 

void opj_thread_pool_wait_completion(opj_thread_pool_t* tp,
                                     int max_remaining_jobs)
{
    if (tp->mutex == NULL) {
        return;
    }

    if (max_remaining_jobs < 0) {
        max_remaining_jobs = 0;
    }
    opj_mutex_lock(tp->mutex);
    tp->signaling_threshold = max_remaining_jobs;
    while (tp->pending_jobs_count > max_remaining_jobs) {
        /*printf("tp=%p, jobs before wait = %d, max_remaining_jobs = %d\n", tp, tp->pending_jobs_count, max_remaining_jobs);*/
        opj_cond_wait(tp->cond, tp->mutex);
        /*printf("tp=%p, jobs after wait = %d\n", tp, tp->pending_jobs_count);*/
    }
    opj_mutex_unlock(tp->mutex);
}