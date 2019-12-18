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
typedef  int /*<<< orphan*/  znode_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  int boolean_t ;
struct TYPE_3__ {int /*<<< orphan*/  i_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACE_ALL_PERMS ; 
 int B_TRUE ; 
 int /*<<< orphan*/  KUID_TO_SUID (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFS_OWNER ; 
 TYPE_1__* ZTOI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZTOZSB (int /*<<< orphan*/ *) ; 
 scalar_t__ secpolicy_vnode_any_access (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_fuid_map_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zfs_zaccess_aces_check (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

boolean_t
zfs_has_access(znode_t *zp, cred_t *cr)
{
	uint32_t have = ACE_ALL_PERMS;

	if (zfs_zaccess_aces_check(zp, &have, B_TRUE, cr) != 0) {
		uid_t owner;

		owner = zfs_fuid_map_id(ZTOZSB(zp),
		    KUID_TO_SUID(ZTOI(zp)->i_uid), cr, ZFS_OWNER);
		return (secpolicy_vnode_any_access(cr, ZTOI(zp), owner) == 0);
	}
	return (B_TRUE);
}