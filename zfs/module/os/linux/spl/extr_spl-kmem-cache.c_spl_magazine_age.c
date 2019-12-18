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
struct TYPE_5__ {scalar_t__ skm_magic; size_t skm_cpu; scalar_t__ skm_avail; int /*<<< orphan*/  skm_refill; scalar_t__ skm_age; } ;
typedef  TYPE_1__ spl_kmem_magazine_t ;
struct TYPE_6__ {int skc_delay; int /*<<< orphan*/  skc_lock; TYPE_1__** skc_mag; } ;
typedef  TYPE_2__ spl_kmem_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int HZ ; 
 scalar_t__ SKM_MAGIC ; 
 int /*<<< orphan*/  __spl_cache_flush (TYPE_2__*,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int irqs_disabled () ; 
 int /*<<< orphan*/  jiffies ; 
 size_t smp_processor_id () ; 
 int /*<<< orphan*/  spin_trylock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 scalar_t__ time_before (int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
spl_magazine_age(void *data)
{
	spl_kmem_cache_t *skc = (spl_kmem_cache_t *)data;
	spl_kmem_magazine_t *skm = skc->skc_mag[smp_processor_id()];

	ASSERT(skm->skm_magic == SKM_MAGIC);
	ASSERT(skm->skm_cpu == smp_processor_id());
	ASSERT(irqs_disabled());

	/* There are no available objects or they are too young to age out */
	if ((skm->skm_avail == 0) ||
	    time_before(jiffies, skm->skm_age + skc->skc_delay * HZ))
		return;

	/*
	 * Because we're executing in interrupt context we may have
	 * interrupted the holder of this lock.  To avoid a potential
	 * deadlock return if the lock is contended.
	 */
	if (!spin_trylock(&skc->skc_lock))
		return;

	__spl_cache_flush(skc, skm, skm->skm_refill);
	spin_unlock(&skc->skc_lock);
}