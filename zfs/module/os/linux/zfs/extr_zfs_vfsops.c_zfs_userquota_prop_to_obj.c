#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  z_projectobjquota_obj; int /*<<< orphan*/  z_projectquota_obj; int /*<<< orphan*/  z_groupobjquota_obj; int /*<<< orphan*/  z_userobjquota_obj; int /*<<< orphan*/  z_groupquota_obj; int /*<<< orphan*/  z_userquota_obj; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  int zfs_userquota_prop_t ;
typedef  int /*<<< orphan*/  uint64_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_GROUPUSED_OBJECT ; 
 int /*<<< orphan*/  DMU_PROJECTUSED_OBJECT ; 
 int /*<<< orphan*/  DMU_USERUSED_OBJECT ; 
 int /*<<< orphan*/  ZFS_NO_OBJECT ; 
#define  ZFS_PROP_GROUPOBJQUOTA 139 
#define  ZFS_PROP_GROUPOBJUSED 138 
#define  ZFS_PROP_GROUPQUOTA 137 
#define  ZFS_PROP_GROUPUSED 136 
#define  ZFS_PROP_PROJECTOBJQUOTA 135 
#define  ZFS_PROP_PROJECTOBJUSED 134 
#define  ZFS_PROP_PROJECTQUOTA 133 
#define  ZFS_PROP_PROJECTUSED 132 
#define  ZFS_PROP_USEROBJQUOTA 131 
#define  ZFS_PROP_USEROBJUSED 130 
#define  ZFS_PROP_USERQUOTA 129 
#define  ZFS_PROP_USERUSED 128 

__attribute__((used)) static uint64_t
zfs_userquota_prop_to_obj(zfsvfs_t *zfsvfs, zfs_userquota_prop_t type)
{
	switch (type) {
	case ZFS_PROP_USERUSED:
	case ZFS_PROP_USEROBJUSED:
		return (DMU_USERUSED_OBJECT);
	case ZFS_PROP_GROUPUSED:
	case ZFS_PROP_GROUPOBJUSED:
		return (DMU_GROUPUSED_OBJECT);
	case ZFS_PROP_PROJECTUSED:
	case ZFS_PROP_PROJECTOBJUSED:
		return (DMU_PROJECTUSED_OBJECT);
	case ZFS_PROP_USERQUOTA:
		return (zfsvfs->z_userquota_obj);
	case ZFS_PROP_GROUPQUOTA:
		return (zfsvfs->z_groupquota_obj);
	case ZFS_PROP_USEROBJQUOTA:
		return (zfsvfs->z_userobjquota_obj);
	case ZFS_PROP_GROUPOBJQUOTA:
		return (zfsvfs->z_groupobjquota_obj);
	case ZFS_PROP_PROJECTQUOTA:
		return (zfsvfs->z_projectquota_obj);
	case ZFS_PROP_PROJECTOBJQUOTA:
		return (zfsvfs->z_projectobjquota_obj);
	default:
		return (ZFS_NO_OBJECT);
	}
}