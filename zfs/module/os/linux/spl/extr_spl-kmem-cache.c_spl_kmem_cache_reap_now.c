#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_7__ {int /*<<< orphan*/  skm_avail; } ;
typedef  TYPE_1__ spl_kmem_magazine_t ;
struct TYPE_8__ {scalar_t__ skc_magic; int skc_flags; scalar_t__ skc_slab_total; scalar_t__ skc_slab_alloc; scalar_t__ skc_obj_alloc; int /*<<< orphan*/  skc_ref; TYPE_1__** skc_mag; int /*<<< orphan*/  skc_private; int /*<<< orphan*/  (* skc_reclaim ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  skc_lock; } ;
typedef  TYPE_2__ spl_kmem_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  KMC_BIT_DESTROY ; 
 int /*<<< orphan*/  KMC_BIT_REAPING ; 
 int KMC_EXPIRE_MEM ; 
 int KMC_SLAB ; 
 scalar_t__ SKC_MAGIC ; 
 scalar_t__ UINT64_MAX ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 size_t smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_cache_flush (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int spl_kmem_cache_expire ; 
 int /*<<< orphan*/  spl_slab_reclaim (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  wake_up_bit (int*,int /*<<< orphan*/ ) ; 

void
spl_kmem_cache_reap_now(spl_kmem_cache_t *skc, int count)
{
	ASSERT(skc->skc_magic == SKC_MAGIC);
	ASSERT(!test_bit(KMC_BIT_DESTROY, &skc->skc_flags));

	atomic_inc(&skc->skc_ref);

	/*
	 * Execute the registered reclaim callback if it exists.
	 */
	if (skc->skc_flags & KMC_SLAB) {
		if (skc->skc_reclaim)
			skc->skc_reclaim(skc->skc_private);
		goto out;
	}

	/*
	 * Prevent concurrent cache reaping when contended.
	 */
	if (test_and_set_bit(KMC_BIT_REAPING, &skc->skc_flags))
		goto out;

	/*
	 * When a reclaim function is available it may be invoked repeatedly
	 * until at least a single slab can be freed.  This ensures that we
	 * do free memory back to the system.  This helps minimize the chance
	 * of an OOM event when the bulk of memory is used by the slab.
	 *
	 * When free slabs are already available the reclaim callback will be
	 * skipped.  Additionally, if no forward progress is detected despite
	 * a reclaim function the cache will be skipped to avoid deadlock.
	 *
	 * Longer term this would be the correct place to add the code which
	 * repacks the slabs in order minimize fragmentation.
	 */
	if (skc->skc_reclaim) {
		uint64_t objects = UINT64_MAX;
		int do_reclaim;

		do {
			spin_lock(&skc->skc_lock);
			do_reclaim =
			    (skc->skc_slab_total > 0) &&
			    ((skc->skc_slab_total-skc->skc_slab_alloc) == 0) &&
			    (skc->skc_obj_alloc < objects);

			objects = skc->skc_obj_alloc;
			spin_unlock(&skc->skc_lock);

			if (do_reclaim)
				skc->skc_reclaim(skc->skc_private);

		} while (do_reclaim);
	}

	/* Reclaim from the magazine and free all now empty slabs. */
	if (spl_kmem_cache_expire & KMC_EXPIRE_MEM) {
		spl_kmem_magazine_t *skm;
		unsigned long irq_flags;

		local_irq_save(irq_flags);
		skm = skc->skc_mag[smp_processor_id()];
		spl_cache_flush(skc, skm, skm->skm_avail);
		local_irq_restore(irq_flags);
	}

	spl_slab_reclaim(skc);
	clear_bit_unlock(KMC_BIT_REAPING, &skc->skc_flags);
	smp_mb__after_atomic();
	wake_up_bit(&skc->skc_flags, KMC_BIT_REAPING);
out:
	atomic_dec(&skc->skc_ref);
}