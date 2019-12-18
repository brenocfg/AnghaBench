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
typedef  scalar_t__ zprop_source_t ;
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  size_t uint_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  fmd_hdl_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  FMD_SLEEP ; 
 int /*<<< orphan*/  VDEV_TYPE_ROOT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_ASHIFT ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PATH ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_SPARES ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_TYPE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_VDEV_TREE ; 
 int /*<<< orphan*/  ZPOOL_PROP_ASHIFT ; 
 scalar_t__ ZPROP_SRC_DEFAULT ; 
 int /*<<< orphan*/  basename (char*) ; 
 int /*<<< orphan*/  fmd_hdl_debug (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fmd_nvl_alloc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  nvlist_add_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int) ; 
 int /*<<< orphan*/  nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_add_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_lookup_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,size_t*) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/ * zpool_get_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int zpool_get_prop_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__*) ; 
 scalar_t__ zpool_vdev_attach (int /*<<< orphan*/ *,char*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* zpool_vdev_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static boolean_t
replace_with_spare(fmd_hdl_t *hdl, zpool_handle_t *zhp, nvlist_t *vdev)
{
	nvlist_t *config, *nvroot, *replacement;
	nvlist_t **spares;
	uint_t s, nspares;
	char *dev_name;
	zprop_source_t source;
	int ashift;

	config = zpool_get_config(zhp, NULL);
	if (nvlist_lookup_nvlist(config, ZPOOL_CONFIG_VDEV_TREE,
	    &nvroot) != 0)
		return (B_FALSE);

	/*
	 * Find out if there are any hot spares available in the pool.
	 */
	if (nvlist_lookup_nvlist_array(nvroot, ZPOOL_CONFIG_SPARES,
	    &spares, &nspares) != 0)
		return (B_FALSE);

	/*
	 * lookup "ashift" pool property, we may need it for the replacement
	 */
	ashift = zpool_get_prop_int(zhp, ZPOOL_PROP_ASHIFT, &source);

	replacement = fmd_nvl_alloc(hdl, FMD_SLEEP);

	(void) nvlist_add_string(replacement, ZPOOL_CONFIG_TYPE,
	    VDEV_TYPE_ROOT);

	dev_name = zpool_vdev_name(NULL, zhp, vdev, B_FALSE);

	/*
	 * Try to replace each spare, ending when we successfully
	 * replace it.
	 */
	for (s = 0; s < nspares; s++) {
		char *spare_name;

		if (nvlist_lookup_string(spares[s], ZPOOL_CONFIG_PATH,
		    &spare_name) != 0)
			continue;

		/* if set, add the "ashift" pool property to the spare nvlist */
		if (source != ZPROP_SRC_DEFAULT)
			(void) nvlist_add_uint64(spares[s],
			    ZPOOL_CONFIG_ASHIFT, ashift);

		(void) nvlist_add_nvlist_array(replacement,
		    ZPOOL_CONFIG_CHILDREN, &spares[s], 1);

		fmd_hdl_debug(hdl, "zpool_vdev_replace '%s' with spare '%s'",
		    dev_name, basename(spare_name));

		if (zpool_vdev_attach(zhp, dev_name, spare_name,
		    replacement, B_TRUE) == 0) {
			free(dev_name);
			nvlist_free(replacement);
			return (B_TRUE);
		}
	}

	free(dev_name);
	nvlist_free(replacement);

	return (B_FALSE);
}