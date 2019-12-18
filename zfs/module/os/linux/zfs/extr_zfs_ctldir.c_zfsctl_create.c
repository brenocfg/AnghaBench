#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * z_ctldir; } ;
typedef  TYPE_1__ zfsvfs_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ENOENT ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZFSCTL_INO_ROOT ; 
 int /*<<< orphan*/ * zfsctl_inode_alloc (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zpl_fops_root ; 
 int /*<<< orphan*/  zpl_ops_root ; 

int
zfsctl_create(zfsvfs_t *zfsvfs)
{
	ASSERT(zfsvfs->z_ctldir == NULL);

	zfsvfs->z_ctldir = zfsctl_inode_alloc(zfsvfs, ZFSCTL_INO_ROOT,
	    &zpl_fops_root, &zpl_ops_root);
	if (zfsvfs->z_ctldir == NULL)
		return (SET_ERROR(ENOENT));

	return (0);
}