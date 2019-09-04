#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */

/* Variables and functions */
 int /*<<< orphan*/  ATOMIC_RELAXED ; 
 int /*<<< orphan*/  atomic_store_b (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_store_p (int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cassert (int /*<<< orphan*/ ) ; 
 void* dss_base ; 
 int /*<<< orphan*/  dss_exhausted ; 
 int /*<<< orphan*/  dss_extending ; 
 int /*<<< orphan*/  dss_max ; 
 void* extent_dss_sbrk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  have_dss ; 

void
extent_dss_boot(void) {
	cassert(have_dss);

	dss_base = extent_dss_sbrk(0);
	atomic_store_b(&dss_extending, false, ATOMIC_RELAXED);
	atomic_store_b(&dss_exhausted, dss_base == (void *)-1, ATOMIC_RELAXED);
	atomic_store_p(&dss_max, dss_base, ATOMIC_RELAXED);
}