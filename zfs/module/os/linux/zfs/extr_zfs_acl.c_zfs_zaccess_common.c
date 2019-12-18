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
struct TYPE_3__ {scalar_t__ z_replay; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  cred_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 TYPE_1__* ZTOZSB (int /*<<< orphan*/ *) ; 
 int zfs_zaccess_aces_check (int /*<<< orphan*/ *,scalar_t__*,scalar_t__,int /*<<< orphan*/ *) ; 
 int zfs_zaccess_dataset_check (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
zfs_zaccess_common(znode_t *zp, uint32_t v4_mode, uint32_t *working_mode,
    boolean_t *check_privs, boolean_t skipaclchk, cred_t *cr)
{
	zfsvfs_t *zfsvfs = ZTOZSB(zp);
	int err;

	*working_mode = v4_mode;
	*check_privs = B_TRUE;

	/*
	 * Short circuit empty requests
	 */
	if (v4_mode == 0 || zfsvfs->z_replay) {
		*working_mode = 0;
		return (0);
	}

	if ((err = zfs_zaccess_dataset_check(zp, v4_mode)) != 0) {
		*check_privs = B_FALSE;
		return (err);
	}

	/*
	 * The caller requested that the ACL check be skipped.  This
	 * would only happen if the caller checked VOP_ACCESS() with a
	 * 32 bit ACE mask and already had the appropriate permissions.
	 */
	if (skipaclchk) {
		*working_mode = 0;
		return (0);
	}

	return (zfs_zaccess_aces_check(zp, working_mode, B_FALSE, cr));
}