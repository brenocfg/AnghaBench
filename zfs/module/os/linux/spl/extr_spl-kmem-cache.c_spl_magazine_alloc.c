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
struct TYPE_6__ {int skm_size; int skm_cpu; int /*<<< orphan*/  skm_age; TYPE_2__* skm_cache; int /*<<< orphan*/  skm_refill; scalar_t__ skm_avail; int /*<<< orphan*/  skm_magic; } ;
typedef  TYPE_1__ spl_kmem_magazine_t ;
struct TYPE_7__ {int skc_mag_size; int /*<<< orphan*/  skc_mag_refill; } ;
typedef  TYPE_2__ spl_kmem_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SKM_MAGIC ; 
 int /*<<< orphan*/  cpu_to_node (int) ; 
 int /*<<< orphan*/  jiffies ; 
 TYPE_1__* kmalloc_node (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static spl_kmem_magazine_t *
spl_magazine_alloc(spl_kmem_cache_t *skc, int cpu)
{
	spl_kmem_magazine_t *skm;
	int size = sizeof (spl_kmem_magazine_t) +
	    sizeof (void *) * skc->skc_mag_size;

	skm = kmalloc_node(size, GFP_KERNEL, cpu_to_node(cpu));
	if (skm) {
		skm->skm_magic = SKM_MAGIC;
		skm->skm_avail = 0;
		skm->skm_size = skc->skc_mag_size;
		skm->skm_refill = skc->skc_mag_refill;
		skm->skm_cache = skc;
		skm->skm_age = jiffies;
		skm->skm_cpu = cpu;
	}

	return (skm);
}