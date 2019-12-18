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
typedef  int /*<<< orphan*/  kcf_reqid_table_t ;
typedef  int /*<<< orphan*/  kcf_pool_t ;
typedef  int /*<<< orphan*/  kcf_global_swq_t ;
struct TYPE_5__ {int /*<<< orphan*/  gs_cv; int /*<<< orphan*/  gs_lock; int /*<<< orphan*/  rt_lock; int /*<<< orphan*/  kp_user_cv; int /*<<< orphan*/  kp_user_lock; int /*<<< orphan*/  kp_nothr_cv; int /*<<< orphan*/  kp_thread_lock; } ;

/* Variables and functions */
 int REQID_TABLES ; 
 int /*<<< orphan*/  cv_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* gswq ; 
 scalar_t__ kcf_areq_cache ; 
 scalar_t__ kcf_context_cache ; 
 scalar_t__ kcf_misc_kstat ; 
 TYPE_1__** kcf_reqid_table ; 
 scalar_t__ kcf_sreq_cache ; 
 TYPE_1__* kcfpool ; 
 int /*<<< orphan*/  kmem_cache_destroy (scalar_t__) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  kstat_delete (scalar_t__) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ntfy_list_cv ; 
 int /*<<< orphan*/  ntfy_list_lock ; 

void
kcf_sched_destroy(void)
{
	int i;

	if (kcf_misc_kstat)
		kstat_delete(kcf_misc_kstat);

	if (kcfpool) {
		mutex_destroy(&kcfpool->kp_thread_lock);
		cv_destroy(&kcfpool->kp_nothr_cv);
		mutex_destroy(&kcfpool->kp_user_lock);
		cv_destroy(&kcfpool->kp_user_cv);

		kmem_free(kcfpool, sizeof (kcf_pool_t));
	}

	for (i = 0; i < REQID_TABLES; i++) {
		if (kcf_reqid_table[i]) {
			mutex_destroy(&(kcf_reqid_table[i]->rt_lock));
			kmem_free(kcf_reqid_table[i],
			    sizeof (kcf_reqid_table_t));
		}
	}

	if (gswq) {
		mutex_destroy(&gswq->gs_lock);
		cv_destroy(&gswq->gs_cv);
		kmem_free(gswq, sizeof (kcf_global_swq_t));
	}

	if (kcf_context_cache)
		kmem_cache_destroy(kcf_context_cache);
	if (kcf_areq_cache)
		kmem_cache_destroy(kcf_areq_cache);
	if (kcf_sreq_cache)
		kmem_cache_destroy(kcf_sreq_cache);

	mutex_destroy(&ntfy_list_lock);
	cv_destroy(&ntfy_list_cv);
}