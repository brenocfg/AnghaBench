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
typedef  int /*<<< orphan*/  vdev_indirect_mapping_t ;
typedef  int /*<<< orphan*/  vdev_indirect_mapping_entry_phys_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/ * vdev_indirect_mapping_entry_for_offset_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

vdev_indirect_mapping_entry_phys_t *
vdev_indirect_mapping_entry_for_offset_or_next(vdev_indirect_mapping_t *vim,
    uint64_t offset)
{
	return (vdev_indirect_mapping_entry_for_offset_impl(vim, offset,
	    B_TRUE));
}