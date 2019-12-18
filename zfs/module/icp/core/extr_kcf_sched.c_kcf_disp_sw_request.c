#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  kcf_areq_node_t ;
struct TYPE_4__ {int /*<<< orphan*/  gs_lock; int /*<<< orphan*/  gs_cv; } ;
struct TYPE_3__ {scalar_t__ kp_idlethreads; int kp_threads; int kp_blockedthreads; int kp_nthrs; int /*<<< orphan*/  kp_user_lock; int /*<<< orphan*/  kp_user_cv; scalar_t__ kp_signal_create_thread; } ;

/* Variables and functions */
 scalar_t__ B_TRUE ; 
 int CRYPTO_QUEUED ; 
 int MIN (int,scalar_t__) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 TYPE_2__* gswq ; 
 int kcf_enqueue (int /*<<< orphan*/ *) ; 
 scalar_t__ kcf_maxthreads ; 
 int kcf_minthreads ; 
 TYPE_1__* kcfpool ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
kcf_disp_sw_request(kcf_areq_node_t *areq)
{
	int err;
	int cnt = 0;

	if ((err = kcf_enqueue(areq)) != 0)
		return (err);

	if (kcfpool->kp_idlethreads > 0) {
		/* Signal an idle thread to run */
		mutex_enter(&gswq->gs_lock);
		cv_signal(&gswq->gs_cv);
		mutex_exit(&gswq->gs_lock);

		return (CRYPTO_QUEUED);
	}

	/*
	 * We keep the number of running threads to be at
	 * kcf_minthreads to reduce gs_lock contention.
	 */
	cnt = kcf_minthreads -
	    (kcfpool->kp_threads - kcfpool->kp_blockedthreads);
	if (cnt > 0) {
		/*
		 * The following ensures the number of threads in pool
		 * does not exceed kcf_maxthreads.
		 */
		cnt = MIN(cnt, kcf_maxthreads - (int)kcfpool->kp_threads);
		if (cnt > 0) {
			/* Signal the creator thread for more threads */
			mutex_enter(&kcfpool->kp_user_lock);
			if (!kcfpool->kp_signal_create_thread) {
				kcfpool->kp_signal_create_thread = B_TRUE;
				kcfpool->kp_nthrs = cnt;
				cv_signal(&kcfpool->kp_user_cv);
			}
			mutex_exit(&kcfpool->kp_user_lock);
		}
	}

	return (CRYPTO_QUEUED);
}