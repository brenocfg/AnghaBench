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
typedef  size_t uint_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  VDEV_ALLOC_BIAS_SPECIAL ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_ALLOCATION_BIAS ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,size_t*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
zpool_has_special_vdev(nvlist_t *nvroot)
{
	nvlist_t **child;
	uint_t children;

	if (nvlist_lookup_nvlist_array(nvroot, ZPOOL_CONFIG_CHILDREN, &child,
	    &children) == 0) {
		for (uint_t c = 0; c < children; c++) {
			char *bias;

			if (nvlist_lookup_string(child[c],
			    ZPOOL_CONFIG_ALLOCATION_BIAS, &bias) == 0 &&
			    strcmp(bias, VDEV_ALLOC_BIAS_SPECIAL) == 0) {
				return (B_TRUE);
			}
		}
	}
	return (B_FALSE);
}