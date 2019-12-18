#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  raidz_test_opts_t ;
struct TYPE_2__ {scalar_t__ rto_sanity; } ;

/* Variables and functions */
 int RAND_MAX ; 
 int /*<<< orphan*/  SWEEP_ERROR ; 
 int /*<<< orphan*/  VERIFY (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cv_signal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  failed_opts ; 
 int /*<<< orphan*/  free_slots ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int rand () ; 
 TYPE_1__ rto_opts ; 
 int run_test (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sem_cv ; 
 int /*<<< orphan*/  sem_mtx ; 
 int /*<<< orphan*/  sweep_state ; 
 int /*<<< orphan*/  thread_exit () ; 
 int /*<<< orphan*/  umem_free (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void
sweep_thread(void *arg)
{
	int err = 0;
	raidz_test_opts_t *opts = (raidz_test_opts_t *)arg;
	VERIFY(opts != NULL);

	err = run_test(opts);

	if (rto_opts.rto_sanity) {
		/* 25% chance that a sweep test fails */
		if (rand() < (RAND_MAX/4))
			err = 1;
	}

	if (0 != err) {
		mutex_enter(&sem_mtx);
		memcpy(&failed_opts, opts, sizeof (raidz_test_opts_t));
		sweep_state = SWEEP_ERROR;
		mutex_exit(&sem_mtx);
	}

	umem_free(opts, sizeof (raidz_test_opts_t));

	/* signal the next thread */
	mutex_enter(&sem_mtx);
	free_slots++;
	cv_signal(&sem_cv);
	mutex_exit(&sem_mtx);

	thread_exit();
}