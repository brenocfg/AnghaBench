#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ skc_magic; int skc_flags; int /*<<< orphan*/  skc_lock; int /*<<< orphan*/  skc_obj_deadlock; int /*<<< orphan*/  skc_waitq; int /*<<< orphan*/  skc_ref; } ;
typedef  TYPE_1__ spl_kmem_cache_t ;
struct TYPE_10__ {int ska_flags; int /*<<< orphan*/  ska_tqe; TYPE_1__* ska_cache; } ;
typedef  TYPE_2__ spl_kmem_alloc_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ASSERT0 (int) ; 
 int EAGAIN ; 
 int ENOMEM ; 
 int HZ ; 
 int /*<<< orphan*/  KMC_BIT_DEADLOCKED ; 
 int /*<<< orphan*/  KMC_BIT_GROWING ; 
 int /*<<< orphan*/  KMC_BIT_REAPING ; 
 int KMC_KVMEM ; 
 int KMC_SLAB ; 
 int KMC_VMEM ; 
 int KM_NOSLEEP ; 
 int KM_PUBLIC_MASK ; 
 scalar_t__ SKC_MAGIC ; 
 int /*<<< orphan*/  TASK_UNINTERRUPTIBLE ; 
 int __spl_cache_grow (TYPE_1__*,int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit_unlock (int /*<<< orphan*/ ,int*) ; 
 TYPE_2__* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_flags_convert (int) ; 
 int /*<<< orphan*/  might_sleep () ; 
 int /*<<< orphan*/  set_bit (int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_cache_grow_wait (TYPE_1__*) ; 
 int /*<<< orphan*/  spl_cache_grow_work ; 
 int spl_emergency_alloc (TYPE_1__*,int,void**) ; 
 int /*<<< orphan*/  spl_kmem_cache_taskq ; 
 int spl_wait_on_bit (int*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  taskq_dispatch_ent (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  taskq_init_ent (int /*<<< orphan*/ *) ; 
 scalar_t__ test_and_set_bit (int /*<<< orphan*/ ,int*) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int*) ; 
 int wait_event_timeout (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
spl_cache_grow(spl_kmem_cache_t *skc, int flags, void **obj)
{
	int remaining, rc = 0;

	ASSERT0(flags & ~KM_PUBLIC_MASK);
	ASSERT(skc->skc_magic == SKC_MAGIC);
	ASSERT((skc->skc_flags & KMC_SLAB) == 0);
	might_sleep();
	*obj = NULL;

	/*
	 * Before allocating a new slab wait for any reaping to complete and
	 * then return so the local magazine can be rechecked for new objects.
	 */
	if (test_bit(KMC_BIT_REAPING, &skc->skc_flags)) {
		rc = spl_wait_on_bit(&skc->skc_flags, KMC_BIT_REAPING,
		    TASK_UNINTERRUPTIBLE);
		return (rc ? rc : -EAGAIN);
	}

	/*
	 * To reduce the overhead of context switch and improve NUMA locality,
	 * it tries to allocate a new slab in the current process context with
	 * KM_NOSLEEP flag. If it fails, it will launch a new taskq to do the
	 * allocation.
	 *
	 * However, this can't be applied to KVM_VMEM due to a bug that
	 * __vmalloc() doesn't honor gfp flags in page table allocation.
	 */
	if (!(skc->skc_flags & KMC_VMEM) && !(skc->skc_flags & KMC_KVMEM)) {
		rc = __spl_cache_grow(skc, flags | KM_NOSLEEP);
		if (rc == 0)
			return (0);
	}

	/*
	 * This is handled by dispatching a work request to the global work
	 * queue.  This allows us to asynchronously allocate a new slab while
	 * retaining the ability to safely fall back to a smaller synchronous
	 * allocations to ensure forward progress is always maintained.
	 */
	if (test_and_set_bit(KMC_BIT_GROWING, &skc->skc_flags) == 0) {
		spl_kmem_alloc_t *ska;

		ska = kmalloc(sizeof (*ska), kmem_flags_convert(flags));
		if (ska == NULL) {
			clear_bit_unlock(KMC_BIT_GROWING, &skc->skc_flags);
			smp_mb__after_atomic();
			wake_up_all(&skc->skc_waitq);
			return (-ENOMEM);
		}

		atomic_inc(&skc->skc_ref);
		ska->ska_cache = skc;
		ska->ska_flags = flags;
		taskq_init_ent(&ska->ska_tqe);
		taskq_dispatch_ent(spl_kmem_cache_taskq,
		    spl_cache_grow_work, ska, 0, &ska->ska_tqe);
	}

	/*
	 * The goal here is to only detect the rare case where a virtual slab
	 * allocation has deadlocked.  We must be careful to minimize the use
	 * of emergency objects which are more expensive to track.  Therefore,
	 * we set a very long timeout for the asynchronous allocation and if
	 * the timeout is reached the cache is flagged as deadlocked.  From
	 * this point only new emergency objects will be allocated until the
	 * asynchronous allocation completes and clears the deadlocked flag.
	 */
	if (test_bit(KMC_BIT_DEADLOCKED, &skc->skc_flags)) {
		rc = spl_emergency_alloc(skc, flags, obj);
	} else {
		remaining = wait_event_timeout(skc->skc_waitq,
		    spl_cache_grow_wait(skc), HZ / 10);

		if (!remaining) {
			spin_lock(&skc->skc_lock);
			if (test_bit(KMC_BIT_GROWING, &skc->skc_flags)) {
				set_bit(KMC_BIT_DEADLOCKED, &skc->skc_flags);
				skc->skc_obj_deadlock++;
			}
			spin_unlock(&skc->skc_lock);
		}

		rc = -ENOMEM;
	}

	return (rc);
}