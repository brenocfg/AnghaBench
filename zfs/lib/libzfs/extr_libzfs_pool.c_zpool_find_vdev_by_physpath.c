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
struct TYPE_3__ {int /*<<< orphan*/  zpool_config; } ;
typedef  TYPE_1__ zpool_handle_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  NV_UNIQUE_NAME ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PHYS_PATH ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ strtoull (char const*,char**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vdev_to_nvlist_iter (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  verify (int) ; 

nvlist_t *
zpool_find_vdev_by_physpath(zpool_handle_t *zhp, const char *ppath,
    boolean_t *avail_spare, boolean_t *l2cache, boolean_t *log)
{
	nvlist_t *search, *nvroot, *ret;
	uint64_t guid;
	char *end;

	verify(nvlist_alloc(&search, NV_UNIQUE_NAME, KM_SLEEP) == 0);

	guid = strtoull(ppath, &end, 0);
	if (guid != 0 && *end == '\0') {
		verify(nvlist_add_uint64(search, ZPOOL_CONFIG_GUID, guid) == 0);
	} else {
		verify(nvlist_add_string(search, ZPOOL_CONFIG_PHYS_PATH,
		    ppath) == 0);
	}

	verify(nvlist_lookup_nvlist(zhp->zpool_config, ZPOOL_CONFIG_VDEV_TREE,
	    &nvroot) == 0);

	*avail_spare = B_FALSE;
	*l2cache = B_FALSE;
	if (log != NULL)
		*log = B_FALSE;
	ret = vdev_to_nvlist_iter(nvroot, search, avail_spare, l2cache, log);
	nvlist_free(search);

	return (ret);
}