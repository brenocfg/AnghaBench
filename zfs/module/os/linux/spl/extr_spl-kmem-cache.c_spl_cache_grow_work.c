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
struct TYPE_5__ {int /*<<< orphan*/  skc_flags; int /*<<< orphan*/  skc_ref; } ;
typedef  TYPE_1__ spl_kmem_cache_t ;
struct TYPE_6__ {int /*<<< orphan*/  ska_flags; TYPE_1__* ska_cache; } ;
typedef  TYPE_2__ spl_kmem_alloc_t ;

/* Variables and functions */
 int /*<<< orphan*/  KMC_BIT_GROWING ; 
 int /*<<< orphan*/  __spl_cache_grow (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (TYPE_2__*) ; 
 int /*<<< orphan*/  smp_mb__after_atomic () ; 
 int /*<<< orphan*/  smp_mb__before_atomic () ; 

__attribute__((used)) static void
spl_cache_grow_work(void *data)
{
	spl_kmem_alloc_t *ska = (spl_kmem_alloc_t *)data;
	spl_kmem_cache_t *skc = ska->ska_cache;

	(void) __spl_cache_grow(skc, ska->ska_flags);

	atomic_dec(&skc->skc_ref);
	smp_mb__before_atomic();
	clear_bit(KMC_BIT_GROWING, &skc->skc_flags);
	smp_mb__after_atomic();

	kfree(ska);
}