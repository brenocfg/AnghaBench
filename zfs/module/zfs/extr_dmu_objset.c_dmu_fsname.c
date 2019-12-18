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
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ENAMETOOLONG ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int ZFS_MAX_DATASET_NAME_LEN ; 
 char* strchr (char const*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 

int
dmu_fsname(const char *snapname, char *buf)
{
	char *atp = strchr(snapname, '@');
	if (atp == NULL)
		return (SET_ERROR(EINVAL));
	if (atp - snapname >= ZFS_MAX_DATASET_NAME_LEN)
		return (SET_ERROR(ENAMETOOLONG));
	(void) strlcpy(buf, snapname, atp - snapname + 1);
	return (0);
}