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
typedef  int /*<<< orphan*/  zfs_handle_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  nvlist_t ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (int) ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_PROP_CREATETXG ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/ * fsavl_find (int /*<<< orphan*/ *,scalar_t__,char**) ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,char*,char**) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char*,char*) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
created_before(libzfs_handle_t *hdl, avl_tree_t *avl,
    uint64_t guid1, uint64_t guid2)
{
	nvlist_t *nvfs;
	char *fsname = NULL, *snapname = NULL;
	char buf[ZFS_MAX_DATASET_NAME_LEN];
	int rv;
	zfs_handle_t *guid1hdl, *guid2hdl;
	uint64_t create1, create2;

	if (guid2 == 0)
		return (0);
	if (guid1 == 0)
		return (1);

	nvfs = fsavl_find(avl, guid1, &snapname);
	VERIFY(0 == nvlist_lookup_string(nvfs, "name", &fsname));
	(void) snprintf(buf, sizeof (buf), "%s@%s", fsname, snapname);
	guid1hdl = zfs_open(hdl, buf, ZFS_TYPE_SNAPSHOT);
	if (guid1hdl == NULL)
		return (-1);

	nvfs = fsavl_find(avl, guid2, &snapname);
	VERIFY(0 == nvlist_lookup_string(nvfs, "name", &fsname));
	(void) snprintf(buf, sizeof (buf), "%s@%s", fsname, snapname);
	guid2hdl = zfs_open(hdl, buf, ZFS_TYPE_SNAPSHOT);
	if (guid2hdl == NULL) {
		zfs_close(guid1hdl);
		return (-1);
	}

	create1 = zfs_prop_get_int(guid1hdl, ZFS_PROP_CREATETXG);
	create2 = zfs_prop_get_int(guid2hdl, ZFS_PROP_CREATETXG);

	if (create1 < create2)
		rv = -1;
	else if (create1 > create2)
		rv = +1;
	else
		rv = 0;

	zfs_close(guid1hdl);
	zfs_close(guid2hdl);

	return (rv);
}