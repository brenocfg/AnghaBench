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
struct TYPE_6__ {TYPE_1__* vim_phys; int /*<<< orphan*/  vim_objset; scalar_t__ vim_havecounts; } ;
typedef  TYPE_2__ vdev_indirect_mapping_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_5__ {int vimp_num_entries; int /*<<< orphan*/  vimp_counts_object; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DMU_READ_PREFETCH ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bzero (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dmu_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_indirect_mapping_verify (TYPE_2__*) ; 
 int /*<<< orphan*/ * vmem_alloc (int,int /*<<< orphan*/ ) ; 

uint32_t *
vdev_indirect_mapping_load_obsolete_counts(vdev_indirect_mapping_t *vim)
{
	ASSERT(vdev_indirect_mapping_verify(vim));

	uint64_t counts_size =
	    vim->vim_phys->vimp_num_entries * sizeof (uint32_t);
	uint32_t *counts = vmem_alloc(counts_size, KM_SLEEP);
	if (vim->vim_havecounts) {
		VERIFY0(dmu_read(vim->vim_objset,
		    vim->vim_phys->vimp_counts_object,
		    0, counts_size,
		    counts, DMU_READ_PREFETCH));
	} else {
		bzero(counts, counts_size);
	}
	return (counts);
}