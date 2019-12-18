#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_6__ {int /*<<< orphan*/ * vdev_spa; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  uberblock_t ;
typedef  int /*<<< orphan*/  spa_t ;

/* Variables and functions */
 int EIO ; 
 int /*<<< orphan*/  vdev_uberblock_sync (int /*<<< orphan*/ *,int*,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 scalar_t__ vdev_writeable (TYPE_1__*) ; 
 int /*<<< orphan*/  zio_flush (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/ * zio_root (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zio_wait (int /*<<< orphan*/ *) ; 

int
vdev_uberblock_sync_list(vdev_t **svd, int svdcount, uberblock_t *ub, int flags)
{
	spa_t *spa = svd[0]->vdev_spa;
	zio_t *zio;
	uint64_t good_writes = 0;

	zio = zio_root(spa, NULL, NULL, flags);

	for (int v = 0; v < svdcount; v++)
		vdev_uberblock_sync(zio, &good_writes, ub, svd[v], flags);

	(void) zio_wait(zio);

	/*
	 * Flush the uberblocks to disk.  This ensures that the odd labels
	 * are no longer needed (because the new uberblocks and the even
	 * labels are safely on disk), so it is safe to overwrite them.
	 */
	zio = zio_root(spa, NULL, NULL, flags);

	for (int v = 0; v < svdcount; v++) {
		if (vdev_writeable(svd[v])) {
			zio_flush(zio, svd[v]);
		}
	}

	(void) zio_wait(zio);

	return (good_writes >= 1 ? 0 : EIO);
}