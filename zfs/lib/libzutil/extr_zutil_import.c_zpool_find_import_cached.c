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
typedef  scalar_t__ uint64_t ;
struct stat64 {scalar_t__ st_size; } ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libpc_handle_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  EZFS_BADCACHE ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  TEXT_DOMAIN ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_CACHEFILE ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_GUID ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_POOL_NAME ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  dgettext (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  errno ; 
 char* fnvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ fnvlist_lookup_uint64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * fnvpair_value_nvlist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ fstat64 (int,struct stat64*) ; 
 scalar_t__ nvlist_add_nvlist (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_add_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*) ; 
 scalar_t__ nvlist_alloc (int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_unpack (char*,scalar_t__,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 int open (char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,char*,scalar_t__) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify (int) ; 
 char* zutil_alloc (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  zutil_error (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zutil_error_aux (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zutil_no_memory (int /*<<< orphan*/ *) ; 
 scalar_t__ zutil_pool_active (int /*<<< orphan*/ *,char*,scalar_t__,scalar_t__*) ; 
 int /*<<< orphan*/ * zutil_refresh_config (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static nvlist_t *
zpool_find_import_cached(libpc_handle_t *hdl, const char *cachefile,
    const char *poolname, uint64_t guid)
{
	char *buf;
	int fd;
	struct stat64 statbuf;
	nvlist_t *raw, *src, *dst;
	nvlist_t *pools;
	nvpair_t *elem;
	char *name;
	uint64_t this_guid;
	boolean_t active;

	verify(poolname == NULL || guid == 0);

	if ((fd = open(cachefile, O_RDONLY)) < 0) {
		zutil_error_aux(hdl, "%s", strerror(errno));
		(void) zutil_error(hdl, EZFS_BADCACHE,
		    dgettext(TEXT_DOMAIN, "failed to open cache file"));
		return (NULL);
	}

	if (fstat64(fd, &statbuf) != 0) {
		zutil_error_aux(hdl, "%s", strerror(errno));
		(void) close(fd);
		(void) zutil_error(hdl, EZFS_BADCACHE,
		    dgettext(TEXT_DOMAIN, "failed to get size of cache file"));
		return (NULL);
	}

	if ((buf = zutil_alloc(hdl, statbuf.st_size)) == NULL) {
		(void) close(fd);
		return (NULL);
	}

	if (read(fd, buf, statbuf.st_size) != statbuf.st_size) {
		(void) close(fd);
		free(buf);
		(void) zutil_error(hdl, EZFS_BADCACHE,
		    dgettext(TEXT_DOMAIN,
		    "failed to read cache file contents"));
		return (NULL);
	}

	(void) close(fd);

	if (nvlist_unpack(buf, statbuf.st_size, &raw, 0) != 0) {
		free(buf);
		(void) zutil_error(hdl, EZFS_BADCACHE,
		    dgettext(TEXT_DOMAIN,
		    "invalid or corrupt cache file contents"));
		return (NULL);
	}

	free(buf);

	/*
	 * Go through and get the current state of the pools and refresh their
	 * state.
	 */
	if (nvlist_alloc(&pools, 0, 0) != 0) {
		(void) zutil_no_memory(hdl);
		nvlist_free(raw);
		return (NULL);
	}

	elem = NULL;
	while ((elem = nvlist_next_nvpair(raw, elem)) != NULL) {
		src = fnvpair_value_nvlist(elem);

		name = fnvlist_lookup_string(src, ZPOOL_CONFIG_POOL_NAME);
		if (poolname != NULL && strcmp(poolname, name) != 0)
			continue;

		this_guid = fnvlist_lookup_uint64(src, ZPOOL_CONFIG_POOL_GUID);
		if (guid != 0 && guid != this_guid)
			continue;

		if (zutil_pool_active(hdl, name, this_guid, &active) != 0) {
			nvlist_free(raw);
			nvlist_free(pools);
			return (NULL);
		}

		if (active)
			continue;

		if (nvlist_add_string(src, ZPOOL_CONFIG_CACHEFILE,
		    cachefile) != 0) {
			(void) zutil_no_memory(hdl);
			nvlist_free(raw);
			nvlist_free(pools);
			return (NULL);
		}

		if ((dst = zutil_refresh_config(hdl, src)) == NULL) {
			nvlist_free(raw);
			nvlist_free(pools);
			return (NULL);
		}

		if (nvlist_add_nvlist(pools, nvpair_name(elem), dst) != 0) {
			(void) zutil_no_memory(hdl);
			nvlist_free(dst);
			nvlist_free(raw);
			nvlist_free(pools);
			return (NULL);
		}
		nvlist_free(dst);
	}

	nvlist_free(raw);
	return (pools);
}