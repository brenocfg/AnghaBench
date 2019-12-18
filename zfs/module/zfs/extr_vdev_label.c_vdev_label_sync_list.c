#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
struct TYPE_11__ {int /*<<< orphan*/ * vdev_aux; scalar_t__ vdev_islog; int /*<<< orphan*/  vdev_ishole; } ;
typedef  TYPE_1__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_12__ {int /*<<< orphan*/  spa_config_dirty_list; } ;
typedef  TYPE_2__ spa_t ;
typedef  int /*<<< orphan*/  list_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/ * kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_1__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_next (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  vdev_label_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vdev_label_sync_ignore_done ; 
 int /*<<< orphan*/  vdev_label_sync_top_done ; 
 int /*<<< orphan*/  zio_flush (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  zio_nowait (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zio_null (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * zio_root (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int zio_wait (int /*<<< orphan*/ *) ; 

int
vdev_label_sync_list(spa_t *spa, int l, uint64_t txg, int flags)
{
	list_t *dl = &spa->spa_config_dirty_list;
	vdev_t *vd;
	zio_t *zio;
	int error;

	/*
	 * Write the new labels to disk.
	 */
	zio = zio_root(spa, NULL, NULL, flags);

	for (vd = list_head(dl); vd != NULL; vd = list_next(dl, vd)) {
		uint64_t *good_writes;

		ASSERT(!vd->vdev_ishole);

		good_writes = kmem_zalloc(sizeof (uint64_t), KM_SLEEP);
		zio_t *vio = zio_null(zio, spa, NULL,
		    (vd->vdev_islog || vd->vdev_aux != NULL) ?
		    vdev_label_sync_ignore_done : vdev_label_sync_top_done,
		    good_writes, flags);
		vdev_label_sync(vio, good_writes, vd, l, txg, flags);
		zio_nowait(vio);
	}

	error = zio_wait(zio);

	/*
	 * Flush the new labels to disk.
	 */
	zio = zio_root(spa, NULL, NULL, flags);

	for (vd = list_head(dl); vd != NULL; vd = list_next(dl, vd))
		zio_flush(zio, vd);

	(void) zio_wait(zio);

	return (error);
}