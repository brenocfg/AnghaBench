#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_6__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ io_child_type; scalar_t__ io_offset; TYPE_3__* io_vd; int /*<<< orphan*/  io_spa; TYPE_6__* io_bp; } ;
typedef  TYPE_2__ zio_t ;
struct TYPE_9__ {TYPE_1__* vdev_ops; } ;
typedef  TYPE_3__ vdev_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  dva_t ;
struct TYPE_10__ {int /*<<< orphan*/ * blk_dva; } ;
struct TYPE_7__ {scalar_t__ vdev_op_leaf; } ;

/* Variables and functions */
 int BP_GET_NDVAS (TYPE_6__*) ; 
 scalar_t__ DVA_GET_OFFSET (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  DVA_GET_VDEV (int /*<<< orphan*/ *) ; 
 scalar_t__ VDEV_LABEL_START_SIZE ; 
 scalar_t__ ZIO_CHILD_VDEV ; 
 int ZI_NO_DVA ; 
 TYPE_3__* vdev_lookup_top (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
zio_match_dva(zio_t *zio)
{
	int i = ZI_NO_DVA;

	if (zio->io_bp != NULL && zio->io_vd != NULL &&
	    zio->io_child_type == ZIO_CHILD_VDEV) {
		for (i = BP_GET_NDVAS(zio->io_bp) - 1; i >= 0; i--) {
			dva_t *dva = &zio->io_bp->blk_dva[i];
			uint64_t off = DVA_GET_OFFSET(dva);
			vdev_t *vd = vdev_lookup_top(zio->io_spa,
			    DVA_GET_VDEV(dva));

			/* Compensate for vdev label added to leaves */
			if (zio->io_vd->vdev_ops->vdev_op_leaf)
				off += VDEV_LABEL_START_SIZE;

			if (zio->io_vd == vd && zio->io_offset == off)
				break;
		}
	}

	return (i);
}