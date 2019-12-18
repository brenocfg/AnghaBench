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
struct TYPE_3__ {int /*<<< orphan*/  vimep_dst; } ;
typedef  TYPE_1__ vdev_indirect_mapping_entry_phys_t ;
typedef  scalar_t__ const uint64_t ;

/* Variables and functions */
 scalar_t__ const DVA_GET_ASIZE (int /*<<< orphan*/ *) ; 
 scalar_t__ DVA_MAPPING_GET_SRC_OFFSET (TYPE_1__ const* const) ; 

__attribute__((used)) static int
dva_mapping_overlap_compare(const void *v_key, const void *v_array_elem)
{
	const uint64_t * const key = v_key;
	const vdev_indirect_mapping_entry_phys_t * const array_elem =
	    v_array_elem;
	uint64_t src_offset = DVA_MAPPING_GET_SRC_OFFSET(array_elem);

	if (*key < src_offset) {
		return (-1);
	} else if (*key < src_offset + DVA_GET_ASIZE(&array_elem->vimep_dst)) {
		return (0);
	} else {
		return (1);
	}
}