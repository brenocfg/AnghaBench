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
typedef  scalar_t__ taskqid_t ;
struct TYPE_5__ {scalar_t__ skc_magic; int skc_flags; int skc_delay; int /*<<< orphan*/  skc_ref; int /*<<< orphan*/  skc_lock; scalar_t__ skc_taskqid; } ;
typedef  TYPE_1__ spl_kmem_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int HZ ; 
 int /*<<< orphan*/  KMC_BIT_DESTROY ; 
 int KMC_EXPIRE_AGE ; 
 int KMC_NOMAGAZINE ; 
 scalar_t__ SKC_MAGIC ; 
 int /*<<< orphan*/  TQ_SLEEP ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 scalar_t__ ddi_get_lbolt () ; 
 int /*<<< orphan*/  on_each_cpu (int /*<<< orphan*/ ,TYPE_1__*,int) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int spl_kmem_cache_expire ; 
 int /*<<< orphan*/  spl_kmem_cache_taskq ; 
 int /*<<< orphan*/  spl_magazine_age ; 
 int /*<<< orphan*/  spl_slab_reclaim (TYPE_1__*) ; 
 int /*<<< orphan*/  taskq_cancel_id (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ taskq_dispatch_delay (int /*<<< orphan*/ ,void (*) (void*),TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static void
spl_cache_age(void *data)
{
	spl_kmem_cache_t *skc = (spl_kmem_cache_t *)data;
	taskqid_t id = 0;

	ASSERT(skc->skc_magic == SKC_MAGIC);

	/* Dynamically disabled at run time */
	if (!(spl_kmem_cache_expire & KMC_EXPIRE_AGE))
		return;

	atomic_inc(&skc->skc_ref);

	if (!(skc->skc_flags & KMC_NOMAGAZINE))
		on_each_cpu(spl_magazine_age, skc, 1);

	spl_slab_reclaim(skc);

	while (!test_bit(KMC_BIT_DESTROY, &skc->skc_flags) && !id) {
		id = taskq_dispatch_delay(
		    spl_kmem_cache_taskq, spl_cache_age, skc, TQ_SLEEP,
		    ddi_get_lbolt() + skc->skc_delay / 3 * HZ);

		/* Destroy issued after dispatch immediately cancel it */
		if (test_bit(KMC_BIT_DESTROY, &skc->skc_flags) && id)
			taskq_cancel_id(spl_kmem_cache_taskq, id);
	}

	spin_lock(&skc->skc_lock);
	skc->skc_taskqid = id;
	spin_unlock(&skc->skc_lock);

	atomic_dec(&skc->skc_ref);
}