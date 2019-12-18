#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int io_flags; int /*<<< orphan*/  io_spa; TYPE_4__* io_vsd; } ;
typedef  TYPE_2__ zio_t ;
struct TYPE_13__ {int /*<<< orphan*/  vs_checksum_errors; } ;
struct TYPE_15__ {int /*<<< orphan*/  vdev_stat_lock; TYPE_1__ vdev_stat; } ;
typedef  TYPE_3__ vdev_t ;
struct TYPE_16__ {int /*<<< orphan*/  iv_splits; } ;
typedef  TYPE_4__ indirect_vsd_t ;
struct TYPE_17__ {int is_children; int /*<<< orphan*/  is_size; int /*<<< orphan*/  is_target_offset; TYPE_6__* is_child; } ;
typedef  TYPE_5__ indirect_split_t ;
struct TYPE_18__ {TYPE_3__* ic_vdev; int /*<<< orphan*/ * ic_data; } ;
typedef  TYPE_6__ indirect_child_t ;

/* Variables and functions */
 int ZIO_FLAG_SPECULATIVE ; 
 TYPE_5__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_5__* list_next (int /*<<< orphan*/ *,TYPE_5__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_ereport_post_checksum (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
vdev_indirect_all_checksum_errors(zio_t *zio)
{
	indirect_vsd_t *iv = zio->io_vsd;

	if (zio->io_flags & ZIO_FLAG_SPECULATIVE)
		return;

	for (indirect_split_t *is = list_head(&iv->iv_splits);
	    is != NULL; is = list_next(&iv->iv_splits, is)) {
		for (int c = 0; c < is->is_children; c++) {
			indirect_child_t *ic = &is->is_child[c];

			if (ic->ic_data == NULL)
				continue;

			vdev_t *vd = ic->ic_vdev;

			mutex_enter(&vd->vdev_stat_lock);
			vd->vdev_stat.vs_checksum_errors++;
			mutex_exit(&vd->vdev_stat_lock);

			zfs_ereport_post_checksum(zio->io_spa, vd, NULL, zio,
			    is->is_target_offset, is->is_size,
			    NULL, NULL, NULL);
		}
	}
}