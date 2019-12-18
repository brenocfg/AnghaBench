#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int (* zfs_iter_f ) (TYPE_1__*,void*) ;
struct TYPE_8__ {int /*<<< orphan*/  zfs_hdl; int /*<<< orphan*/  zfs_name; } ;
typedef  TYPE_1__ zfs_handle_t ;
struct mnttab {char* mnt_fstype; char* mnt_special; } ;
typedef  int /*<<< orphan*/  mnt_prop ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int ENOENT ; 
 int /*<<< orphan*/  MNTTAB ; 
 char* MNTTYPE_ZFS ; 
 int ZFS_MAXPROPLEN ; 
 int /*<<< orphan*/  ZFS_PROP_MOUNTPOINT ; 
 int /*<<< orphan*/  ZFS_TYPE_FILESYSTEM ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ getmntent (int /*<<< orphan*/ *,struct mnttab*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 size_t strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/  zfs_close (TYPE_1__*) ; 
 TYPE_1__* zfs_open (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get (TYPE_1__*,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int
zfs_iter_mounted(zfs_handle_t *zhp, zfs_iter_f func, void *data)
{
	char mnt_prop[ZFS_MAXPROPLEN];
	struct mnttab entry;
	zfs_handle_t *mtab_zhp;
	size_t namelen = strlen(zhp->zfs_name);
	FILE *mnttab;
	int err = 0;

	if ((mnttab = fopen(MNTTAB, "r")) == NULL)
		return (ENOENT);

	while (err == 0 && getmntent(mnttab, &entry) == 0) {
		/* Ignore non-ZFS entries */
		if (strcmp(entry.mnt_fstype, MNTTYPE_ZFS) != 0)
			continue;

		/* Ignore datasets not within the provided dataset */
		if (strncmp(entry.mnt_special, zhp->zfs_name, namelen) != 0 ||
		    (entry.mnt_special[namelen] != '/' &&
		    entry.mnt_special[namelen] != '@'))
			continue;

		if ((mtab_zhp = zfs_open(zhp->zfs_hdl, entry.mnt_special,
		    ZFS_TYPE_FILESYSTEM)) == NULL)
			continue;

		/* Ignore legacy mounts as they are user managed */
		verify(zfs_prop_get(mtab_zhp, ZFS_PROP_MOUNTPOINT, mnt_prop,
		    sizeof (mnt_prop), NULL, NULL, 0, B_FALSE) == 0);
		if (strcmp(mnt_prop, "legacy") == 0) {
			zfs_close(mtab_zhp);
			continue;
		}

		err = func(mtab_zhp, data);
	}

	fclose(mnttab);

	return (err);
}