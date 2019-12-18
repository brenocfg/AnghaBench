#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  znode_t ;
struct TYPE_5__ {int /*<<< orphan*/  zgd_lr; scalar_t__ zgd_db; int /*<<< orphan*/ * zgd_private; } ;
typedef  TYPE_1__ zgd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ZTOI (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_buf_rele (scalar_t__,TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  zfs_iput_async (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_rangelock_exit (int /*<<< orphan*/ ) ; 

void
zfs_get_done(zgd_t *zgd, int error)
{
	znode_t *zp = zgd->zgd_private;

	if (zgd->zgd_db)
		dmu_buf_rele(zgd->zgd_db, zgd);

	zfs_rangelock_exit(zgd->zgd_lr);

	/*
	 * Release the vnode asynchronously as we currently have the
	 * txg stopped from syncing.
	 */
	zfs_iput_async(ZTOI(zp));

	kmem_free(zgd, sizeof (zgd_t));
}