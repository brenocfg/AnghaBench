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
typedef  int /*<<< orphan*/  zfsvfs_t ;
struct TYPE_3__ {scalar_t__ z_fuid; scalar_t__ z_fgid; } ;
typedef  TYPE_1__ zfs_acl_ids_t ;
typedef  scalar_t__ uint64_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_GROUPUSED_OBJECT ; 
 int /*<<< orphan*/  DMU_PROJECTUSED_OBJECT ; 
 int /*<<< orphan*/  DMU_USERUSED_OBJECT ; 
 scalar_t__ ZFS_DEFAULT_PROJID ; 
 scalar_t__ ZFS_INVALID_PROJID ; 
 scalar_t__ zfs_id_overquota (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

boolean_t
zfs_acl_ids_overquota(zfsvfs_t *zv, zfs_acl_ids_t *acl_ids, uint64_t projid)
{
	return (zfs_id_overquota(zv, DMU_USERUSED_OBJECT, acl_ids->z_fuid) ||
	    zfs_id_overquota(zv, DMU_GROUPUSED_OBJECT, acl_ids->z_fgid) ||
	    (projid != ZFS_DEFAULT_PROJID && projid != ZFS_INVALID_PROJID &&
	    zfs_id_overquota(zv, DMU_PROJECTUSED_OBJECT, projid)));
}