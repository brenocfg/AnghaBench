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
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_TRUE ; 
#define  DATA_TYPE_STRING 129 
#define  DATA_TYPE_UINT64 128 
 int /*<<< orphan*/  ZPOOL_CONFIG_CHILDREN ; 
 char* ZPOOL_CONFIG_GUID ; 
 char* ZPOOL_CONFIG_ID ; 
 char* ZPOOL_CONFIG_IS_LOG ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_L2CACHE ; 
 char* ZPOOL_CONFIG_PATH ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_SPARES ; 
 char* ZPOOL_CONFIG_TYPE ; 
 char* ZPOOL_CONFIG_WHOLE_DISK ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ nvlist_lookup_nvlist_array (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ***,size_t*) ; 
 int /*<<< orphan*/  nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 scalar_t__ nvlist_lookup_uint64 (int /*<<< orphan*/ *,char*,scalar_t__*) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* nvpair_name (int /*<<< orphan*/ *) ; 
 int nvpair_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvpair_value_string (int /*<<< orphan*/ *,char**) ; 
 int /*<<< orphan*/  nvpair_value_uint64 (int /*<<< orphan*/ *,scalar_t__*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 char* strdup (char*) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  strncmp (char*,char*,int /*<<< orphan*/ ) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ strtoull (char*,char**,int) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/  zfs_strcmp_pathname (char*,char*,scalar_t__) ; 
 int zpool_vdev_is_interior (char*) ; 

__attribute__((used)) static nvlist_t *
vdev_to_nvlist_iter(nvlist_t *nv, nvlist_t *search, boolean_t *avail_spare,
    boolean_t *l2cache, boolean_t *log)
{
	uint_t c, children;
	nvlist_t **child;
	nvlist_t *ret;
	uint64_t is_log;
	char *srchkey;
	nvpair_t *pair = nvlist_next_nvpair(search, NULL);

	/* Nothing to look for */
	if (search == NULL || pair == NULL)
		return (NULL);

	/* Obtain the key we will use to search */
	srchkey = nvpair_name(pair);

	switch (nvpair_type(pair)) {
	case DATA_TYPE_UINT64:
		if (strcmp(srchkey, ZPOOL_CONFIG_GUID) == 0) {
			uint64_t srchval, theguid;

			verify(nvpair_value_uint64(pair, &srchval) == 0);
			verify(nvlist_lookup_uint64(nv, ZPOOL_CONFIG_GUID,
			    &theguid) == 0);
			if (theguid == srchval)
				return (nv);
		}
		break;

	case DATA_TYPE_STRING: {
		char *srchval, *val;

		verify(nvpair_value_string(pair, &srchval) == 0);
		if (nvlist_lookup_string(nv, srchkey, &val) != 0)
			break;

		/*
		 * Search for the requested value. Special cases:
		 *
		 * - ZPOOL_CONFIG_PATH for whole disk entries.  These end in
		 *   "-part1", or "p1".  The suffix is hidden from the user,
		 *   but included in the string, so this matches around it.
		 * - ZPOOL_CONFIG_PATH for short names zfs_strcmp_shortname()
		 *   is used to check all possible expanded paths.
		 * - looking for a top-level vdev name (i.e. ZPOOL_CONFIG_TYPE).
		 *
		 * Otherwise, all other searches are simple string compares.
		 */
		if (strcmp(srchkey, ZPOOL_CONFIG_PATH) == 0) {
			uint64_t wholedisk = 0;

			(void) nvlist_lookup_uint64(nv, ZPOOL_CONFIG_WHOLE_DISK,
			    &wholedisk);
			if (zfs_strcmp_pathname(srchval, val, wholedisk) == 0)
				return (nv);

		} else if (strcmp(srchkey, ZPOOL_CONFIG_TYPE) == 0 && val) {
			char *type, *idx, *end, *p;
			uint64_t id, vdev_id;

			/*
			 * Determine our vdev type, keeping in mind
			 * that the srchval is composed of a type and
			 * vdev id pair (i.e. mirror-4).
			 */
			if ((type = strdup(srchval)) == NULL)
				return (NULL);

			if ((p = strrchr(type, '-')) == NULL) {
				free(type);
				break;
			}
			idx = p + 1;
			*p = '\0';

			/*
			 * If the types don't match then keep looking.
			 */
			if (strncmp(val, type, strlen(val)) != 0) {
				free(type);
				break;
			}

			verify(zpool_vdev_is_interior(type));
			verify(nvlist_lookup_uint64(nv, ZPOOL_CONFIG_ID,
			    &id) == 0);

			errno = 0;
			vdev_id = strtoull(idx, &end, 10);

			free(type);
			if (errno != 0)
				return (NULL);

			/*
			 * Now verify that we have the correct vdev id.
			 */
			if (vdev_id == id)
				return (nv);
		}

		/*
		 * Common case
		 */
		if (strcmp(srchval, val) == 0)
			return (nv);
		break;
	}

	default:
		break;
	}

	if (nvlist_lookup_nvlist_array(nv, ZPOOL_CONFIG_CHILDREN,
	    &child, &children) != 0)
		return (NULL);

	for (c = 0; c < children; c++) {
		if ((ret = vdev_to_nvlist_iter(child[c], search,
		    avail_spare, l2cache, NULL)) != NULL) {
			/*
			 * The 'is_log' value is only set for the toplevel
			 * vdev, not the leaf vdevs.  So we always lookup the
			 * log device from the root of the vdev tree (where
			 * 'log' is non-NULL).
			 */
			if (log != NULL &&
			    nvlist_lookup_uint64(child[c],
			    ZPOOL_CONFIG_IS_LOG, &is_log) == 0 &&
			    is_log) {
				*log = B_TRUE;
			}
			return (ret);
		}
	}

	if (nvlist_lookup_nvlist_array(nv, ZPOOL_CONFIG_SPARES,
	    &child, &children) == 0) {
		for (c = 0; c < children; c++) {
			if ((ret = vdev_to_nvlist_iter(child[c], search,
			    avail_spare, l2cache, NULL)) != NULL) {
				*avail_spare = B_TRUE;
				return (ret);
			}
		}
	}

	if (nvlist_lookup_nvlist_array(nv, ZPOOL_CONFIG_L2CACHE,
	    &child, &children) == 0) {
		for (c = 0; c < children; c++) {
			if ((ret = vdev_to_nvlist_iter(child[c], search,
			    avail_spare, l2cache, NULL)) != NULL) {
				*l2cache = B_TRUE;
				return (ret);
			}
		}
	}

	return (NULL);
}