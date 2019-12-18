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

/* Variables and functions */
 char* dm_get_underlying_path (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* realpath (char const*,int /*<<< orphan*/ *) ; 
 char* zfs_strip_partition_path (char*) ; 

char *
zfs_get_underlying_path(const char *dev_name)
{
	char *name = NULL;
	char *tmp;

	if (dev_name == NULL)
		return (NULL);

	tmp = dm_get_underlying_path(dev_name);

	/* dev_name not a DM device, so just un-symlinkize it */
	if (tmp == NULL)
		tmp = realpath(dev_name, NULL);

	if (tmp != NULL) {
		name = zfs_strip_partition_path(tmp);
		free(tmp);
	}

	return (name);
}