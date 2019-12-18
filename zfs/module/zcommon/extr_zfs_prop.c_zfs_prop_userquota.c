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
typedef  size_t zfs_userquota_prop_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 size_t ZFS_NUM_USERQUOTA_PROPS ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zfs_userquota_prop_prefixes ; 

boolean_t
zfs_prop_userquota(const char *name)
{
	zfs_userquota_prop_t prop;

	for (prop = 0; prop < ZFS_NUM_USERQUOTA_PROPS; prop++) {
		if (strncmp(name, zfs_userquota_prop_prefixes[prop],
		    strlen(zfs_userquota_prop_prefixes[prop])) == 0) {
			return (B_TRUE);
		}
	}

	return (B_FALSE);
}