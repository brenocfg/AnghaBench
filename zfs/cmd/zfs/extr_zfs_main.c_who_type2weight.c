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
typedef  int zfs_deleg_who_type_t ;

/* Variables and functions */
#define  ZFS_DELEG_CREATE 137 
#define  ZFS_DELEG_CREATE_SETS 136 
#define  ZFS_DELEG_EVERYONE 135 
#define  ZFS_DELEG_EVERYONE_SETS 134 
#define  ZFS_DELEG_GROUP 133 
#define  ZFS_DELEG_GROUP_SETS 132 
#define  ZFS_DELEG_NAMED_SET 131 
#define  ZFS_DELEG_NAMED_SET_SETS 130 
#define  ZFS_DELEG_USER 129 
#define  ZFS_DELEG_USER_SETS 128 

__attribute__((used)) static int
who_type2weight(zfs_deleg_who_type_t who_type)
{
	int res;
	switch (who_type) {
		case ZFS_DELEG_NAMED_SET_SETS:
		case ZFS_DELEG_NAMED_SET:
			res = 0;
			break;
		case ZFS_DELEG_CREATE_SETS:
		case ZFS_DELEG_CREATE:
			res = 1;
			break;
		case ZFS_DELEG_USER_SETS:
		case ZFS_DELEG_USER:
			res = 2;
			break;
		case ZFS_DELEG_GROUP_SETS:
		case ZFS_DELEG_GROUP:
			res = 3;
			break;
		case ZFS_DELEG_EVERYONE_SETS:
		case ZFS_DELEG_EVERYONE:
			res = 4;
			break;
		default:
			res = -1;
	}

	return (res);
}