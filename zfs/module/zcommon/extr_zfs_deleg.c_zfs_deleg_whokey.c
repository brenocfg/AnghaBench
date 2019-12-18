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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  longlong_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
#define  ZFS_DELEG_CREATE 137 
#define  ZFS_DELEG_CREATE_SETS 136 
#define  ZFS_DELEG_EVERYONE 135 
#define  ZFS_DELEG_EVERYONE_SETS 134 
 int ZFS_DELEG_FIELD_SEP_CHR ; 
#define  ZFS_DELEG_GROUP 133 
#define  ZFS_DELEG_GROUP_SETS 132 
#define  ZFS_DELEG_NAMED_SET 131 
#define  ZFS_DELEG_NAMED_SET_SETS 130 
#define  ZFS_DELEG_USER 129 
#define  ZFS_DELEG_USER_SETS 128 
 int ZFS_MAX_DELEG_NAME ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,char,...) ; 

void
zfs_deleg_whokey(char *attr, zfs_deleg_who_type_t type,
    char inheritchr, void *data)
{
	int len = ZFS_MAX_DELEG_NAME;
	uint64_t *id = data;

	switch (type) {
	case ZFS_DELEG_USER:
	case ZFS_DELEG_GROUP:
	case ZFS_DELEG_USER_SETS:
	case ZFS_DELEG_GROUP_SETS:
		(void) snprintf(attr, len, "%c%c%c%lld", type, inheritchr,
		    ZFS_DELEG_FIELD_SEP_CHR, (longlong_t)*id);
		break;
	case ZFS_DELEG_NAMED_SET_SETS:
	case ZFS_DELEG_NAMED_SET:
		(void) snprintf(attr, len, "%c-%c%s", type,
		    ZFS_DELEG_FIELD_SEP_CHR, (char *)data);
		break;
	case ZFS_DELEG_CREATE:
	case ZFS_DELEG_CREATE_SETS:
		(void) snprintf(attr, len, "%c-%c", type,
		    ZFS_DELEG_FIELD_SEP_CHR);
		break;
	case ZFS_DELEG_EVERYONE:
	case ZFS_DELEG_EVERYONE_SETS:
		(void) snprintf(attr, len, "%c%c%c", type, inheritchr,
		    ZFS_DELEG_FIELD_SEP_CHR);
		break;
	default:
		ASSERT(!"bad zfs_deleg_who_type_t");
	}
}