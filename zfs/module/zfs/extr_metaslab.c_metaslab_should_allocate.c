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
typedef  unsigned long long uint64_t ;
struct TYPE_3__ {scalar_t__ ms_max_size; scalar_t__ ms_unload_time; unsigned long long ms_weight; scalar_t__ ms_loaded; } ;
typedef  TYPE_1__ metaslab_t ;
typedef  int boolean_t ;

/* Variables and functions */
 unsigned long long METASLAB_WEIGHT_TYPE ; 
 scalar_t__ SEC2NSEC (int /*<<< orphan*/ ) ; 
 int WEIGHT_GET_INDEX (unsigned long long) ; 
 int /*<<< orphan*/  WEIGHT_IS_SPACEBASED (unsigned long long) ; 
 scalar_t__ gethrtime () ; 
 int /*<<< orphan*/  zfs_metaslab_max_size_cache_sec ; 

boolean_t
metaslab_should_allocate(metaslab_t *msp, uint64_t asize, boolean_t try_hard)
{
	/*
	 * If the metaslab is loaded, ms_max_size is definitive and we can use
	 * the fast check. If it's not, the ms_max_size is a lower bound (once
	 * set), and we should use the fast check as long as we're not in
	 * try_hard and it's been less than zfs_metaslab_max_size_cache_sec
	 * seconds since the metaslab was unloaded.
	 */
	if (msp->ms_loaded ||
	    (msp->ms_max_size != 0 && !try_hard && gethrtime() <
	    msp->ms_unload_time + SEC2NSEC(zfs_metaslab_max_size_cache_sec)))
		return (msp->ms_max_size >= asize);

	boolean_t should_allocate;
	if (!WEIGHT_IS_SPACEBASED(msp->ms_weight)) {
		/*
		 * The metaslab segment weight indicates segments in the
		 * range [2^i, 2^(i+1)), where i is the index in the weight.
		 * Since the asize might be in the middle of the range, we
		 * should attempt the allocation if asize < 2^(i+1).
		 */
		should_allocate = (asize <
		    1ULL << (WEIGHT_GET_INDEX(msp->ms_weight) + 1));
	} else {
		should_allocate = (asize <=
		    (msp->ms_weight & ~METASLAB_WEIGHT_TYPE));
	}

	return (should_allocate);
}