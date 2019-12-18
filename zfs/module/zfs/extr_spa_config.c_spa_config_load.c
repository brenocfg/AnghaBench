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
typedef  int /*<<< orphan*/  uint64_t ;
struct _buf {int dummy; } ;
typedef  int /*<<< orphan*/  nvpair_t ;
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 scalar_t__ DATA_TYPE_NVLIST ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MAXPATHLEN ; 
 int /*<<< orphan*/ * fnvpair_value_nvlist (int /*<<< orphan*/ *) ; 
 void* kmem_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kobj_close_file (struct _buf*) ; 
 scalar_t__ kobj_get_filesize (struct _buf*,int /*<<< orphan*/ *) ; 
 struct _buf* kobj_open_file (char*) ; 
 scalar_t__ kobj_read_file (struct _buf*,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nvlist_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * nvlist_next_nvpair (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nvlist_unpack (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nvpair_name (int /*<<< orphan*/ *) ; 
 scalar_t__ nvpair_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  spa_add (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 char* spa_config_path ; 
 int /*<<< orphan*/ * spa_lookup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 scalar_t__ zfs_autoimport_disable ; 

void
spa_config_load(void)
{
	void *buf = NULL;
	nvlist_t *nvlist, *child;
	nvpair_t *nvpair;
	char *pathname;
	struct _buf *file;
	uint64_t fsize;

#ifdef _KERNEL
	if (zfs_autoimport_disable)
		return;
#endif

	/*
	 * Open the configuration file.
	 */
	pathname = kmem_alloc(MAXPATHLEN, KM_SLEEP);

	(void) snprintf(pathname, MAXPATHLEN, "%s", spa_config_path);

	file = kobj_open_file(pathname);

	kmem_free(pathname, MAXPATHLEN);

	if (file == (struct _buf *)-1)
		return;

	if (kobj_get_filesize(file, &fsize) != 0)
		goto out;

	buf = kmem_alloc(fsize, KM_SLEEP);

	/*
	 * Read the nvlist from the file.
	 */
	if (kobj_read_file(file, buf, fsize, 0) < 0)
		goto out;

	/*
	 * Unpack the nvlist.
	 */
	if (nvlist_unpack(buf, fsize, &nvlist, KM_SLEEP) != 0)
		goto out;

	/*
	 * Iterate over all elements in the nvlist, creating a new spa_t for
	 * each one with the specified configuration.
	 */
	mutex_enter(&spa_namespace_lock);
	nvpair = NULL;
	while ((nvpair = nvlist_next_nvpair(nvlist, nvpair)) != NULL) {
		if (nvpair_type(nvpair) != DATA_TYPE_NVLIST)
			continue;

		child = fnvpair_value_nvlist(nvpair);

		if (spa_lookup(nvpair_name(nvpair)) != NULL)
			continue;
		(void) spa_add(nvpair_name(nvpair), child, NULL);
	}
	mutex_exit(&spa_namespace_lock);

	nvlist_free(nvlist);

out:
	if (buf != NULL)
		kmem_free(buf, fsize);

	kobj_close_file(file);
}