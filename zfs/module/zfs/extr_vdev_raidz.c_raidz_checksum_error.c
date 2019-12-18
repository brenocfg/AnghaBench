#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {int io_flags; int /*<<< orphan*/  io_bookmark; int /*<<< orphan*/  io_spa; TYPE_6__* io_vsd; TYPE_1__* io_vd; } ;
typedef  TYPE_3__ zio_t ;
struct TYPE_16__ {int /*<<< orphan*/  zbc_injected; scalar_t__ zbc_has_cksum; } ;
typedef  TYPE_4__ zio_bad_cksum_t ;
struct TYPE_14__ {int /*<<< orphan*/  vs_checksum_errors; } ;
struct TYPE_17__ {int /*<<< orphan*/  vdev_stat_lock; TYPE_2__ vdev_stat; } ;
typedef  TYPE_5__ vdev_t ;
struct TYPE_18__ {int /*<<< orphan*/  rm_ecksuminjected; } ;
typedef  TYPE_6__ raidz_map_t ;
struct TYPE_19__ {size_t rc_devidx; int /*<<< orphan*/  rc_abd; int /*<<< orphan*/  rc_size; int /*<<< orphan*/  rc_offset; } ;
typedef  TYPE_7__ raidz_col_t ;
typedef  int /*<<< orphan*/  abd_t ;
struct TYPE_13__ {TYPE_5__** vdev_child; } ;

/* Variables and functions */
 int ZIO_FLAG_SPECULATIVE ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_ereport_post_checksum (int /*<<< orphan*/ ,TYPE_5__*,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 

__attribute__((used)) static void
raidz_checksum_error(zio_t *zio, raidz_col_t *rc, abd_t *bad_data)
{
	vdev_t *vd = zio->io_vd->vdev_child[rc->rc_devidx];

	if (!(zio->io_flags & ZIO_FLAG_SPECULATIVE)) {
		zio_bad_cksum_t zbc;
		raidz_map_t *rm = zio->io_vsd;

		mutex_enter(&vd->vdev_stat_lock);
		vd->vdev_stat.vs_checksum_errors++;
		mutex_exit(&vd->vdev_stat_lock);

		zbc.zbc_has_cksum = 0;
		zbc.zbc_injected = rm->rm_ecksuminjected;

		zfs_ereport_post_checksum(zio->io_spa, vd,
		    &zio->io_bookmark, zio, rc->rc_offset, rc->rc_size,
		    rc->rc_abd, bad_data, &zbc);
	}
}