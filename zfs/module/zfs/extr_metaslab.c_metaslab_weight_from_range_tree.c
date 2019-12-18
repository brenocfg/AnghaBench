#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint8_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int uint32_t ;
struct TYPE_9__ {TYPE_3__* ms_allocatable; TYPE_2__* ms_group; int /*<<< orphan*/  ms_loaded; } ;
typedef  TYPE_4__ metaslab_t ;
struct TYPE_8__ {scalar_t__* rt_histogram; } ;
struct TYPE_7__ {TYPE_1__* mg_vd; } ;
struct TYPE_6__ {int vdev_ashift; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int RANGE_TREE_HISTOGRAM_SIZE ; 
 int SPACE_MAP_HISTOGRAM_SIZE ; 
 int SPA_MINBLOCKSHIFT ; 
 int /*<<< orphan*/  WEIGHT_SET_ACTIVE (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  WEIGHT_SET_COUNT (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  WEIGHT_SET_INDEX (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static uint64_t
metaslab_weight_from_range_tree(metaslab_t *msp)
{
	uint64_t weight = 0;
	uint32_t segments = 0;

	ASSERT(msp->ms_loaded);

	for (int i = RANGE_TREE_HISTOGRAM_SIZE - 1; i >= SPA_MINBLOCKSHIFT;
	    i--) {
		uint8_t shift = msp->ms_group->mg_vd->vdev_ashift;
		int max_idx = SPACE_MAP_HISTOGRAM_SIZE + shift - 1;

		segments <<= 1;
		segments += msp->ms_allocatable->rt_histogram[i];

		/*
		 * The range tree provides more precision than the space map
		 * and must be downgraded so that all values fit within the
		 * space map's histogram. This allows us to compare loaded
		 * vs. unloaded metaslabs to determine which metaslab is
		 * considered "best".
		 */
		if (i > max_idx)
			continue;

		if (segments != 0) {
			WEIGHT_SET_COUNT(weight, segments);
			WEIGHT_SET_INDEX(weight, i);
			WEIGHT_SET_ACTIVE(weight, 0);
			break;
		}
	}
	return (weight);
}