#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int io_flags; scalar_t__ io_child_type; scalar_t__ io_stage; } ;
typedef  TYPE_1__ zio_t ;
typedef  int /*<<< orphan*/  zio_suspend_reason_t ;
struct TYPE_14__ {int /*<<< orphan*/  spa_suspend_lock; TYPE_1__* spa_suspend_zio_root; int /*<<< orphan*/  spa_suspended; } ;
typedef  TYPE_2__ spa_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  CE_WARN ; 
 int /*<<< orphan*/  FM_EREPORT_ZFS_IO_FAILURE ; 
 scalar_t__ ZIO_CHILD_LOGICAL ; 
 scalar_t__ ZIO_FAILURE_MODE_PANIC ; 
 int ZIO_FLAG_CANFAIL ; 
 int ZIO_FLAG_GODFATHER ; 
 int ZIO_FLAG_SPECULATIVE ; 
 scalar_t__ ZIO_STAGE_DONE ; 
 int /*<<< orphan*/  cmn_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fm_panic (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_get_failmode (TYPE_2__*) ; 
 int /*<<< orphan*/  spa_name (TYPE_2__*) ; 
 int /*<<< orphan*/  zfs_ereport_post (int /*<<< orphan*/ ,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_add_child (TYPE_1__*,TYPE_1__*) ; 
 TYPE_1__* zio_root (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * zio_unique_parent (TYPE_1__*) ; 

void
zio_suspend(spa_t *spa, zio_t *zio, zio_suspend_reason_t reason)
{
	if (spa_get_failmode(spa) == ZIO_FAILURE_MODE_PANIC)
		fm_panic("Pool '%s' has encountered an uncorrectable I/O "
		    "failure and the failure mode property for this pool "
		    "is set to panic.", spa_name(spa));

	cmn_err(CE_WARN, "Pool '%s' has encountered an uncorrectable I/O "
	    "failure and has been suspended.\n", spa_name(spa));

	zfs_ereport_post(FM_EREPORT_ZFS_IO_FAILURE, spa, NULL,
	    NULL, NULL, 0, 0);

	mutex_enter(&spa->spa_suspend_lock);

	if (spa->spa_suspend_zio_root == NULL)
		spa->spa_suspend_zio_root = zio_root(spa, NULL, NULL,
		    ZIO_FLAG_CANFAIL | ZIO_FLAG_SPECULATIVE |
		    ZIO_FLAG_GODFATHER);

	spa->spa_suspended = reason;

	if (zio != NULL) {
		ASSERT(!(zio->io_flags & ZIO_FLAG_GODFATHER));
		ASSERT(zio != spa->spa_suspend_zio_root);
		ASSERT(zio->io_child_type == ZIO_CHILD_LOGICAL);
		ASSERT(zio_unique_parent(zio) == NULL);
		ASSERT(zio->io_stage == ZIO_STAGE_DONE);
		zio_add_child(spa->spa_suspend_zio_root, zio);
	}

	mutex_exit(&spa->spa_suspend_lock);
}