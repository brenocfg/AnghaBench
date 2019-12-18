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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libpc_handle_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_DEVID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PATH ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,size_t*) ; 
 int nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 

__attribute__((used)) static int
label_paths_impl(libpc_handle_t *hdl, nvlist_t *nvroot, uint64_t pool_guid,
    uint64_t vdev_guid, char **path, char **devid)
{
	nvlist_t **child;
	uint_t c, children;
	uint64_t guid;
	char *val;
	int error;

	if (nvlist_lookup_nvlist_array(nvroot, ZPOOL_CONFIG_CHILDREN,
	    &child, &children) == 0) {
		for (c = 0; c < children; c++) {
			error  = label_paths_impl(hdl, child[c],
			    pool_guid, vdev_guid, path, devid);
			if (error)
				return (error);
		}
		return (0);
	}

	if (nvroot == NULL)
		return (0);

	error = nvlist_lookup_uint64(nvroot, ZPOOL_CONFIG_GUID, &guid);
	if ((error != 0) || (guid != vdev_guid))
		return (0);

	error = nvlist_lookup_string(nvroot, ZPOOL_CONFIG_PATH, &val);
	if (error == 0)
		*path = val;

	error = nvlist_lookup_string(nvroot, ZPOOL_CONFIG_DEVID, &val);
	if (error == 0)
		*devid = val;

	return (0);
}