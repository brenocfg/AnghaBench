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
typedef  int /*<<< orphan*/  uid_t ;
typedef  int /*<<< orphan*/  mode_t ;
typedef  int /*<<< orphan*/  cred_t ;
struct TYPE_3__ {int /*<<< orphan*/  i_uid; } ;

/* Variables and functions */
 int /*<<< orphan*/  KUID_TO_SUID (int /*<<< orphan*/ ) ; 
 int S_IWUSR ; 
 int S_IXUSR ; 
 int /*<<< orphan*/  ZFS_OWNER ; 
 TYPE_1__* ZTOI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZTOZSB (int /*<<< orphan*/ *) ; 
 int secpolicy_vnode_access2 (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zfs_fuid_map_id (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int zfs_sticky_remove_access (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zfs_delete_final_check(znode_t *zp, znode_t *dzp,
    mode_t available_perms, cred_t *cr)
{
	int error;
	uid_t downer;

	downer = zfs_fuid_map_id(ZTOZSB(dzp), KUID_TO_SUID(ZTOI(dzp)->i_uid),
	    cr, ZFS_OWNER);

	error = secpolicy_vnode_access2(cr, ZTOI(dzp),
	    downer, available_perms, S_IWUSR|S_IXUSR);

	if (error == 0)
		error = zfs_sticky_remove_access(dzp, zp, cr);

	return (error);
}