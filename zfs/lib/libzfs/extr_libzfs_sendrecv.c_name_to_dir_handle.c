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
typedef  int /*<<< orphan*/  libzfs_handle_t ;

/* Variables and functions */
 int ZFS_MAX_DATASET_NAME_LEN ; 
 int /*<<< orphan*/  ZFS_TYPE_DATASET ; 
 char* strchr (char*,char) ; 
 int /*<<< orphan*/  strlcpy (char*,char const*,int) ; 
 int /*<<< orphan*/ * zfs_open (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

zfs_handle_t *
name_to_dir_handle(libzfs_handle_t *hdl, const char *snapname)
{
	char dirname[ZFS_MAX_DATASET_NAME_LEN];
	(void) strlcpy(dirname, snapname, ZFS_MAX_DATASET_NAME_LEN);
	char *c = strchr(dirname, '@');
	if (c != NULL)
		*c = '\0';
	return (zfs_open(hdl, dirname, ZFS_TYPE_DATASET));
}