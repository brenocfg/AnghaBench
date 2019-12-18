#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct kmem_cache {int dummy; } ;
struct TYPE_6__ {scalar_t__ skm_magic; size_t skm_avail; int /*<<< orphan*/  skm_age; void** skm_objs; } ;
typedef  TYPE_1__ spl_kmem_magazine_t ;
struct TYPE_7__ {scalar_t__ skc_magic; int skc_flags; int /*<<< orphan*/  skc_private; int /*<<< orphan*/  (* skc_ctor ) (void*,int /*<<< orphan*/ ,int) ;int /*<<< orphan*/  skc_obj_align; TYPE_1__** skc_mag; int /*<<< orphan*/  skc_lock; int /*<<< orphan*/  skc_obj_alloc; struct kmem_cache* skc_linux_cache; } ;
typedef  TYPE_2__ spl_kmem_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (void*) ; 
 int /*<<< orphan*/  ASSERT0 (int) ; 
 void* IS_P2ALIGNED (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KMC_BIT_DESTROY ; 
 int KMC_SLAB ; 
 int KM_NOSLEEP ; 
 int KM_PUBLIC_MASK ; 
 scalar_t__ SKC_MAGIC ; 
 scalar_t__ SKM_MAGIC ; 
 int /*<<< orphan*/  jiffies ; 
 void* kmem_cache_alloc (struct kmem_cache*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_flags_convert (int) ; 
 scalar_t__ likely (size_t) ; 
 int /*<<< orphan*/  local_irq_disable () ; 
 int /*<<< orphan*/  local_irq_enable () ; 
 int /*<<< orphan*/  prefetchw (void*) ; 
 size_t smp_processor_id () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 void* spl_cache_refill (TYPE_2__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub1 (void*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int*) ; 

void *
spl_kmem_cache_alloc(spl_kmem_cache_t *skc, int flags)
{
	spl_kmem_magazine_t *skm;
	void *obj = NULL;

	ASSERT0(flags & ~KM_PUBLIC_MASK);
	ASSERT(skc->skc_magic == SKC_MAGIC);
	ASSERT(!test_bit(KMC_BIT_DESTROY, &skc->skc_flags));

	/*
	 * Allocate directly from a Linux slab.  All optimizations are left
	 * to the underlying cache we only need to guarantee that KM_SLEEP
	 * callers will never fail.
	 */
	if (skc->skc_flags & KMC_SLAB) {
		struct kmem_cache *slc = skc->skc_linux_cache;
		do {
			obj = kmem_cache_alloc(slc, kmem_flags_convert(flags));
		} while ((obj == NULL) && !(flags & KM_NOSLEEP));

		if (obj != NULL) {
			/*
			 * Even though we leave everything up to the
			 * underlying cache we still keep track of
			 * how many objects we've allocated in it for
			 * better debuggability.
			 */
			spin_lock(&skc->skc_lock);
			skc->skc_obj_alloc++;
			spin_unlock(&skc->skc_lock);
		}
		goto ret;
	}

	local_irq_disable();

restart:
	/*
	 * Safe to update per-cpu structure without lock, but
	 * in the restart case we must be careful to reacquire
	 * the local magazine since this may have changed
	 * when we need to grow the cache.
	 */
	skm = skc->skc_mag[smp_processor_id()];
	ASSERT(skm->skm_magic == SKM_MAGIC);

	if (likely(skm->skm_avail)) {
		/* Object available in CPU cache, use it */
		obj = skm->skm_objs[--skm->skm_avail];
		skm->skm_age = jiffies;
	} else {
		obj = spl_cache_refill(skc, skm, flags);
		if ((obj == NULL) && !(flags & KM_NOSLEEP))
			goto restart;

		local_irq_enable();
		goto ret;
	}

	local_irq_enable();
	ASSERT(obj);
	ASSERT(IS_P2ALIGNED(obj, skc->skc_obj_align));

ret:
	/* Pre-emptively migrate object to CPU L1 cache */
	if (obj) {
		if (obj && skc->skc_ctor)
			skc->skc_ctor(obj, skc->skc_private, flags);
		else
			prefetchw(obj);
	}

	return (obj);
}