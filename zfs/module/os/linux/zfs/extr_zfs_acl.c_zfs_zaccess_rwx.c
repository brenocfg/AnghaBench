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
typedef  int /*<<< orphan*/  znode_t ;
typedef  int mode_t ;
typedef  int /*<<< orphan*/  cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  zfs_unix_to_v4 (int) ; 
 int zfs_zaccess (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int
zfs_zaccess_rwx(znode_t *zp, mode_t mode, int flags, cred_t *cr)
{
	return (zfs_zaccess(zp, zfs_unix_to_v4(mode >> 6), flags, B_FALSE, cr));
}