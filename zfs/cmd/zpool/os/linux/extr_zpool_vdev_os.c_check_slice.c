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
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  blkid_cache ;

/* Variables and functions */
 char* blkid_get_tag_value (int /*<<< orphan*/ ,char*,char const*) ; 
 int check_file (char const*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gettext (char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  vdev_error (int /*<<< orphan*/ ,char const*,char*) ; 

__attribute__((used)) static int
check_slice(const char *path, blkid_cache cache, int force, boolean_t isspare)
{
	int err;
	char *value;

	/* No valid type detected device is safe to use */
	value = blkid_get_tag_value(cache, "TYPE", path);
	if (value == NULL)
		return (0);

	/*
	 * If libblkid detects a ZFS device, we check the device
	 * using check_file() to see if it's safe.  The one safe
	 * case is a spare device shared between multiple pools.
	 */
	if (strcmp(value, "zfs_member") == 0) {
		err = check_file(path, force, isspare);
	} else {
		if (force) {
			err = 0;
		} else {
			err = -1;
			vdev_error(gettext("%s contains a filesystem of "
			    "type '%s'\n"), path, value);
		}
	}

	free(value);

	return (err);
}