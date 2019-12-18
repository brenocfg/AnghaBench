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
typedef  int /*<<< orphan*/  mountb ;
typedef  int /*<<< orphan*/  mounta ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int MAXPATHLEN ; 
 int /*<<< orphan*/  ZFS_PROP_MOUNTPOINT ; 
 int /*<<< orphan*/  ZFS_PROP_ZONED ; 
 scalar_t__ ZFS_TYPE_FILESYSTEM ; 
 int strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  verify (int) ; 
 int /*<<< orphan*/  zfs_get_name (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_get_type (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_prop_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_prop_get_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
mountpoint_cmp(const void *arga, const void *argb)
{
	zfs_handle_t *const *zap = arga;
	zfs_handle_t *za = *zap;
	zfs_handle_t *const *zbp = argb;
	zfs_handle_t *zb = *zbp;
	char mounta[MAXPATHLEN];
	char mountb[MAXPATHLEN];
	const char *a = mounta;
	const char *b = mountb;
	boolean_t gota, gotb;
	uint64_t zoneda, zonedb;

	zoneda = zfs_prop_get_int(za, ZFS_PROP_ZONED);
	zonedb = zfs_prop_get_int(zb, ZFS_PROP_ZONED);
	if (zoneda && !zonedb)
		return (1);
	if (!zoneda && zonedb)
		return (-1);

	gota = (zfs_get_type(za) == ZFS_TYPE_FILESYSTEM);
	if (gota) {
		verify(zfs_prop_get(za, ZFS_PROP_MOUNTPOINT, mounta,
		    sizeof (mounta), NULL, NULL, 0, B_FALSE) == 0);
	}
	gotb = (zfs_get_type(zb) == ZFS_TYPE_FILESYSTEM);
	if (gotb) {
		verify(zfs_prop_get(zb, ZFS_PROP_MOUNTPOINT, mountb,
		    sizeof (mountb), NULL, NULL, 0, B_FALSE) == 0);
	}

	if (gota && gotb) {
		while (*a != '\0' && (*a == *b)) {
			a++;
			b++;
		}
		if (*a == *b)
			return (0);
		if (*a == '\0')
			return (-1);
		if (*b == '\0')
			return (1);
		if (*a == '/')
			return (-1);
		if (*b == '/')
			return (1);
		return (*a < *b ? -1 : *a > *b);
	}

	if (gota)
		return (-1);
	if (gotb)
		return (1);

	/*
	 * If neither filesystem has a mountpoint, revert to sorting by
	 * dataset name.
	 */
	return (strcmp(zfs_get_name(za), zfs_get_name(zb)));
}