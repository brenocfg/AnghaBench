#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct aggsum_bucket {scalar_t__ asc_borrowed; scalar_t__ asc_delta; int /*<<< orphan*/  asc_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  as_lower_bound; int /*<<< orphan*/  as_upper_bound; int /*<<< orphan*/  as_lock; } ;
typedef  TYPE_1__ aggsum_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_add_64 (int /*<<< orphan*/  volatile*,scalar_t__) ; 

__attribute__((used)) static void
aggsum_flush_bucket(aggsum_t *as, struct aggsum_bucket *asb)
{
	ASSERT(MUTEX_HELD(&as->as_lock));
	ASSERT(MUTEX_HELD(&asb->asc_lock));

	/*
	 * We use atomic instructions for this because we read the upper and
	 * lower bounds without the lock, so we need stores to be atomic.
	 */
	atomic_add_64((volatile uint64_t *)&as->as_lower_bound, asb->asc_delta);
	atomic_add_64((volatile uint64_t *)&as->as_upper_bound, asb->asc_delta);
	asb->asc_delta = 0;
	atomic_add_64((volatile uint64_t *)&as->as_upper_bound,
	    -asb->asc_borrowed);
	atomic_add_64((volatile uint64_t *)&as->as_lower_bound,
	    asb->asc_borrowed);
	asb->asc_borrowed = 0;
}