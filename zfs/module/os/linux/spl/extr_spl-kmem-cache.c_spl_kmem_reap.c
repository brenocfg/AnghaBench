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
struct shrink_control {int /*<<< orphan*/  gfp_mask; int /*<<< orphan*/  nr_to_scan; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  KMC_REAP_CHUNK ; 
 int /*<<< orphan*/  __spl_kmem_cache_generic_shrinker (int /*<<< orphan*/ *,struct shrink_control*) ; 

void
spl_kmem_reap(void)
{
	struct shrink_control sc;

	sc.nr_to_scan = KMC_REAP_CHUNK;
	sc.gfp_mask = GFP_KERNEL;

	(void) __spl_kmem_cache_generic_shrinker(NULL, &sc);
}