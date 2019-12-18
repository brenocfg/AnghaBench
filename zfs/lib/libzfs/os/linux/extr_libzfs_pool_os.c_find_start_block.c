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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  scalar_t__ diskaddr_t ;

/* Variables and functions */
 scalar_t__ MAXOFFSET_T ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_WHOLE_DISK ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,size_t*) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ read_efi_label (int /*<<< orphan*/ *,scalar_t__*) ; 

__attribute__((used)) static diskaddr_t
find_start_block(nvlist_t *config)
{
	nvlist_t **child;
	uint_t c, children;
	diskaddr_t sb = MAXOFFSET_T;
	uint64_t wholedisk;

	if (nvlist_lookup_nvlist_array(config,
	    ZPOOL_CONFIG_CHILDREN, &child, &children) != 0) {
		if (nvlist_lookup_uint64(config,
		    ZPOOL_CONFIG_WHOLE_DISK,
		    &wholedisk) != 0 || !wholedisk) {
			return (MAXOFFSET_T);
		}
		if (read_efi_label(config, &sb) < 0)
			sb = MAXOFFSET_T;
		return (sb);
	}

	for (c = 0; c < children; c++) {
		sb = find_start_block(child[c]);
		if (sb != MAXOFFSET_T) {
			return (sb);
		}
	}
	return (MAXOFFSET_T);
}