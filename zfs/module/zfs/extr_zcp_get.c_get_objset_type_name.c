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
typedef  int zfs_type_t ;
typedef  int /*<<< orphan*/  dsl_dataset_t ;

/* Variables and functions */
 int EINVAL ; 
#define  ZFS_TYPE_FILESYSTEM 130 
#define  ZFS_TYPE_SNAPSHOT 129 
#define  ZFS_TYPE_VOLUME 128 
 int get_objset_type (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 

__attribute__((used)) static int
get_objset_type_name(dsl_dataset_t *ds, char *str)
{
	int error;
	zfs_type_t type;
	error = get_objset_type(ds, &type);
	if (error != 0)
		return (error);
	switch (type) {
	case ZFS_TYPE_SNAPSHOT:
		(void) strcpy(str, "snapshot");
		break;
	case ZFS_TYPE_FILESYSTEM:
		(void) strcpy(str, "filesystem");
		break;
	case ZFS_TYPE_VOLUME:
		(void) strcpy(str, "volume");
		break;
	default:
		return (EINVAL);
	}
	return (0);
}