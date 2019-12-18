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
typedef  int /*<<< orphan*/  nvlist_t ;

/* Variables and functions */
 int EZFS_NODEVICE ; 
 int EZFS_NOSPC ; 
 int /*<<< orphan*/  ZPOOL_CONFIG_PHYS_PATH ; 
 scalar_t__ nvlist_lookup_string (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char**) ; 
 size_t snprintf (char*,size_t,char const*,char*) ; 

__attribute__((used)) static int
vdev_get_one_physpath(nvlist_t *config, char *physpath, size_t physpath_size,
    size_t *bytes_written)
{
	size_t bytes_left, pos, rsz;
	char *tmppath;
	const char *format;

	if (nvlist_lookup_string(config, ZPOOL_CONFIG_PHYS_PATH,
	    &tmppath) != 0)
		return (EZFS_NODEVICE);

	pos = *bytes_written;
	bytes_left = physpath_size - pos;
	format = (pos == 0) ? "%s" : " %s";

	rsz = snprintf(physpath + pos, bytes_left, format, tmppath);
	*bytes_written += rsz;

	if (rsz >= bytes_left) {
		/* if physpath was not copied properly, clear it */
		if (bytes_left != 0) {
			physpath[pos] = 0;
		}
		return (EZFS_NOSPC);
	}
	return (0);
}