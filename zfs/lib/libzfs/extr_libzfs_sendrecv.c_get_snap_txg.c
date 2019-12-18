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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  name ;
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_PROP_CREATETXG ; 
 int /*<<< orphan*/  ZFS_TYPE_SNAPSHOT ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 
 int /*<<< orphan*/  zfs_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_dataset_exists (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_prop_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint64_t
get_snap_txg(libzfs_handle_t *hdl, const char *fs, const char *snap)
{
	char name[ZFS_MAX_DATASET_NAME_LEN];
	uint64_t txg = 0;

	if (fs == NULL || fs[0] == '\0' || snap == NULL || snap[0] == '\0')
		return (txg);

	(void) snprintf(name, sizeof (name), "%s@%s", fs, snap);
	if (zfs_dataset_exists(hdl, name, ZFS_TYPE_SNAPSHOT)) {
		zfs_handle_t *zhp = zfs_open(hdl, name, ZFS_TYPE_SNAPSHOT);
		if (zhp != NULL) {
			txg = zfs_prop_get_int(zhp, ZFS_PROP_CREATETXG);
			zfs_close(zhp);
		}
	}

	return (txg);
}