#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  z_flags; int /*<<< orphan*/  z_type; int /*<<< orphan*/  z_fuid; int /*<<< orphan*/  z_access_mask; } ;
typedef  TYPE_1__ zfs_oldace_t ;
typedef  int /*<<< orphan*/  zfs_acl_t ;
typedef  int /*<<< orphan*/  umode_t ;
typedef  size_t caddr_t ;
struct TYPE_6__ {int /*<<< orphan*/  a_who; int /*<<< orphan*/  a_flags; int /*<<< orphan*/  a_type; int /*<<< orphan*/  a_access_mask; } ;
typedef  TYPE_2__ ace_t ;

/* Variables and functions */
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  EINVAL ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_ace_valid (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zfs_copy_ace_2_oldace(umode_t obj_mode, zfs_acl_t *aclp, ace_t *acep,
    zfs_oldace_t *z_acl, int aclcnt, size_t *size)
{
	int i;
	zfs_oldace_t *aceptr = z_acl;

	for (i = 0; i != aclcnt; i++, aceptr++) {
		aceptr->z_access_mask = acep[i].a_access_mask;
		aceptr->z_type = acep[i].a_type;
		aceptr->z_flags = acep[i].a_flags;
		aceptr->z_fuid = acep[i].a_who;
		/*
		 * Make sure ACE is valid
		 */
		if (zfs_ace_valid(obj_mode, aclp, aceptr->z_type,
		    aceptr->z_flags) != B_TRUE)
			return (SET_ERROR(EINVAL));
	}
	*size = (caddr_t)aceptr - (caddr_t)z_acl;
	return (0);
}