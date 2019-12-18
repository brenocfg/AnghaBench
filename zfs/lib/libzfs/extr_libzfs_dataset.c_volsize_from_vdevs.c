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
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  size_t uint_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int SPA_OLD_MAXBLOCKSIZE ; 
 int /*<<< orphan*/  VDEV_TYPE_RAIDZ ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_ASHIFT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_NPARITY ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,size_t*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 
 int vdev_raidz_asize (size_t,int,int,int) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t
volsize_from_vdevs(zpool_handle_t *zhp, uint64_t nblocks, uint64_t blksize)
{
	nvlist_t *config, *tree, **vdevs;
	uint_t nvdevs, v;
	uint64_t ret = 0;

	config = zpool_get_config(zhp, NULL);
	if (nvlist_lookup_nvlist(config, ZPOOL_CONFIG_VDEV_TREE, &tree) != 0 ||
	    nvlist_lookup_nvlist_array(tree, ZPOOL_CONFIG_CHILDREN,
	    &vdevs, &nvdevs) != 0) {
		return (nblocks * blksize);
	}

	for (v = 0; v < nvdevs; v++) {
		char *type;
		uint64_t nparity, ashift, asize, tsize;
		nvlist_t **disks;
		uint_t ndisks;
		uint64_t volsize;

		if (nvlist_lookup_string(vdevs[v], ZPOOL_CONFIG_TYPE,
		    &type) != 0 || strcmp(type, VDEV_TYPE_RAIDZ) != 0 ||
		    nvlist_lookup_uint64(vdevs[v], ZPOOL_CONFIG_NPARITY,
		    &nparity) != 0 ||
		    nvlist_lookup_uint64(vdevs[v], ZPOOL_CONFIG_ASHIFT,
		    &ashift) != 0 ||
		    nvlist_lookup_nvlist_array(vdevs[v], ZPOOL_CONFIG_CHILDREN,
		    &disks, &ndisks) != 0) {
			continue;
		}

		/* allocation size for the "typical" 128k block */
		tsize = vdev_raidz_asize(ndisks, nparity, ashift,
		    SPA_OLD_MAXBLOCKSIZE);
		/* allocation size for the blksize block */
		asize = vdev_raidz_asize(ndisks, nparity, ashift, blksize);

		/*
		 * Scale this size down as a ratio of 128k / tsize.  See theory
		 * statement above.
		 */
		volsize = nblocks * asize * SPA_OLD_MAXBLOCKSIZE / tsize;
		if (volsize > ret) {
			ret = volsize;
		}
	}

	if (ret == 0) {
		ret = nblocks * blksize;
	}

	return (ret);
}