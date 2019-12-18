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
struct TYPE_3__ {int /*<<< orphan*/  z_hints; int /*<<< orphan*/  z_version; } ;
typedef  TYPE_1__ zfs_acl_t ;
typedef  int /*<<< orphan*/  umode_t ;
typedef  int uint16_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
#define  ACE_ACCESS_ALLOWED_OBJECT_ACE_TYPE 131 
#define  ACE_ACCESS_DENIED_OBJECT_ACE_TYPE 130 
 int ACE_DIRECTORY_INHERIT_ACE ; 
 int ACE_FILE_INHERIT_ACE ; 
 int ACE_INHERIT_ONLY_ACE ; 
 int ACE_NO_PROPAGATE_INHERIT_ACE ; 
#define  ACE_SYSTEM_ALARM_OBJECT_ACE_TYPE 129 
#define  ACE_SYSTEM_AUDIT_OBJECT_ACE_TYPE 128 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 scalar_t__ S_ISDIR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_ACL_OBJ_ACE ; 
 int /*<<< orphan*/  ZFS_ACL_VERSION_FUID ; 
 int /*<<< orphan*/  ZFS_INHERIT_ACE ; 
 int /*<<< orphan*/  zfs_acl_valid_ace_type (int,int) ; 

__attribute__((used)) static boolean_t
zfs_ace_valid(umode_t obj_mode, zfs_acl_t *aclp, uint16_t type, uint16_t iflags)
{
	/*
	 * first check type of entry
	 */

	if (!zfs_acl_valid_ace_type(type, iflags))
		return (B_FALSE);

	switch (type) {
	case ACE_ACCESS_ALLOWED_OBJECT_ACE_TYPE:
	case ACE_ACCESS_DENIED_OBJECT_ACE_TYPE:
	case ACE_SYSTEM_AUDIT_OBJECT_ACE_TYPE:
	case ACE_SYSTEM_ALARM_OBJECT_ACE_TYPE:
		if (aclp->z_version < ZFS_ACL_VERSION_FUID)
			return (B_FALSE);
		aclp->z_hints |= ZFS_ACL_OBJ_ACE;
	}

	/*
	 * next check inheritance level flags
	 */

	if (S_ISDIR(obj_mode) &&
	    (iflags & (ACE_FILE_INHERIT_ACE|ACE_DIRECTORY_INHERIT_ACE)))
		aclp->z_hints |= ZFS_INHERIT_ACE;

	if (iflags & (ACE_INHERIT_ONLY_ACE|ACE_NO_PROPAGATE_INHERIT_ACE)) {
		if ((iflags & (ACE_FILE_INHERIT_ACE|
		    ACE_DIRECTORY_INHERIT_ACE)) == 0) {
			return (B_FALSE);
		}
	}

	return (B_TRUE);
}