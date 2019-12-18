#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ skm_magic; scalar_t__ skm_avail; scalar_t__ skm_size; void** skm_objs; int /*<<< orphan*/  skm_refill; } ;
typedef  TYPE_1__ spl_kmem_magazine_t ;
struct TYPE_9__ {scalar_t__ skc_magic; int skc_flags; scalar_t__ skc_obj_emergency; TYPE_1__** skc_mag; int /*<<< orphan*/  skc_lock; int /*<<< orphan*/  skc_obj_alloc; int /*<<< orphan*/  skc_linux_cache; int /*<<< orphan*/  skc_private; int /*<<< orphan*/  (* skc_dtor ) (void*,int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ spl_kmem_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  KMC_BIT_DESTROY ; 
 int KMC_SLAB ; 
 scalar_t__ SKC_MAGIC ; 
 scalar_t__ SKM_MAGIC ; 
 int /*<<< orphan*/  is_vmalloc_addr (void*) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  local_irq_restore (unsigned long) ; 
 int /*<<< orphan*/  local_irq_save (unsigned long) ; 
 size_t smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_cache_flush (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ spl_emergency_free (TYPE_2__*,void*) ; 
 int /*<<< orphan*/  spl_slab_reclaim (TYPE_2__*) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ unlikely (int) ; 

void
spl_kmem_cache_free(spl_kmem_cache_t *skc, void *obj)
{
	spl_kmem_magazine_t *skm;
	unsigned long flags;
	int do_reclaim = 0;
	int do_emergency = 0;

	ASSERT(skc->skc_magic == SKC_MAGIC);
	ASSERT(!test_bit(KMC_BIT_DESTROY, &skc->skc_flags));

	/*
	 * Run the destructor
	 */
	if (skc->skc_dtor)
		skc->skc_dtor(obj, skc->skc_private);

	/*
	 * Free the object from the Linux underlying Linux slab.
	 */
	if (skc->skc_flags & KMC_SLAB) {
		kmem_cache_free(skc->skc_linux_cache, obj);
		spin_lock(&skc->skc_lock);
		skc->skc_obj_alloc--;
		spin_unlock(&skc->skc_lock);
		return;
	}

	/*
	 * While a cache has outstanding emergency objects all freed objects
	 * must be checked.  However, since emergency objects will never use
	 * a virtual address these objects can be safely excluded as an
	 * optimization.
	 */
	if (!is_vmalloc_addr(obj)) {
		spin_lock(&skc->skc_lock);
		do_emergency = (skc->skc_obj_emergency > 0);
		spin_unlock(&skc->skc_lock);

		if (do_emergency && (spl_emergency_free(skc, obj) == 0))
			return;
	}

	local_irq_save(flags);

	/*
	 * Safe to update per-cpu structure without lock, but
	 * no remote memory allocation tracking is being performed
	 * it is entirely possible to allocate an object from one
	 * CPU cache and return it to another.
	 */
	skm = skc->skc_mag[smp_processor_id()];
	ASSERT(skm->skm_magic == SKM_MAGIC);

	/*
	 * Per-CPU cache full, flush it to make space for this object,
	 * this may result in an empty slab which can be reclaimed once
	 * interrupts are re-enabled.
	 */
	if (unlikely(skm->skm_avail >= skm->skm_size)) {
		spl_cache_flush(skc, skm, skm->skm_refill);
		do_reclaim = 1;
	}

	/* Available space in cache, use it */
	skm->skm_objs[skm->skm_avail++] = obj;

	local_irq_restore(flags);

	if (do_reclaim)
		spl_slab_reclaim(skc);
}