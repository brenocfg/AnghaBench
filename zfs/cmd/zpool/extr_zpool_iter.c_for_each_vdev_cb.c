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
typedef  scalar_t__ uint64_t ;
typedef  int (* pool_vdev_iter_f ) (int /*<<< orphan*/ *,int /*<<< orphan*/ *,void*) ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int ARRAY_SIZE (char const**) ; 
 int /*<<< orphan*/  VDEV_TYPE_ROOT ; 
 char const* ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_IS_HOLE ; 
 char const* ZPOOL_CONFIG_L2CACHE ; 
 char const* ZPOOL_CONFIG_SPARES ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ***,size_t*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  nvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
for_each_vdev_cb(zpool_handle_t *zhp, nvlist_t *nv, pool_vdev_iter_f func,
    void *data)
{
	nvlist_t **child;
	uint_t c, children;
	int ret = 0;
	int i;
	char *type;

	const char *list[] = {
	    ZPOOL_CONFIG_SPARES,
	    ZPOOL_CONFIG_L2CACHE,
	    ZPOOL_CONFIG_CHILDREN
	};

	for (i = 0; i < ARRAY_SIZE(list); i++) {
		if (nvlist_lookup_nvlist_array(nv, list[i], &child,
		    &children) == 0) {
			for (c = 0; c < children; c++) {
				uint64_t ishole = 0;

				(void) nvlist_lookup_uint64(child[c],
				    ZPOOL_CONFIG_IS_HOLE, &ishole);

				if (ishole)
					continue;

				ret |= for_each_vdev_cb(zhp, child[c], func,
				    data);
			}
		}
	}

	if (nvlist_lookup_string(nv, ZPOOL_CONFIG_TYPE, &type) != 0)
		return (ret);

	/* Don't run our function on root vdevs */
	if (strcmp(type, VDEV_TYPE_ROOT) != 0) {
		ret |= func(zhp, nv, data);
	}

	return (ret);
}