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
struct TYPE_9__ {TYPE_1__* vim_phys; int /*<<< orphan*/ * vim_dbuf; scalar_t__ vim_object; int /*<<< orphan*/ * vim_objset; int /*<<< orphan*/ * vim_entries; } ;
typedef  TYPE_2__ vdev_indirect_mapping_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {scalar_t__ vimp_num_entries; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_buf_rele (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  vdev_indirect_mapping_size (TYPE_2__*) ; 
 int /*<<< orphan*/  vdev_indirect_mapping_verify (TYPE_2__*) ; 
 int /*<<< orphan*/  vmem_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void
vdev_indirect_mapping_close(vdev_indirect_mapping_t *vim)
{
	ASSERT(vdev_indirect_mapping_verify(vim));

	if (vim->vim_phys->vimp_num_entries > 0) {
		uint64_t map_size = vdev_indirect_mapping_size(vim);
		vmem_free(vim->vim_entries, map_size);
		vim->vim_entries = NULL;
	}

	dmu_buf_rele(vim->vim_dbuf, vim);

	vim->vim_objset = NULL;
	vim->vim_object = 0;
	vim->vim_dbuf = NULL;
	vim->vim_phys = NULL;

	kmem_free(vim, sizeof (*vim));
}