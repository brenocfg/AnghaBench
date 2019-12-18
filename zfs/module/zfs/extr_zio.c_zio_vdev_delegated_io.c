#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zio_type_t ;
typedef  int /*<<< orphan*/  zio_t ;
typedef  int /*<<< orphan*/  zio_priority_t ;
typedef  int /*<<< orphan*/  zio_done_func_t ;
struct TYPE_6__ {int /*<<< orphan*/  vdev_spa; TYPE_1__* vdev_ops; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  enum zio_flag { ____Placeholder_zio_flag } zio_flag ;
typedef  int /*<<< orphan*/  abd_t ;
struct TYPE_5__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int ZIO_FLAG_CANFAIL ; 
 int ZIO_FLAG_DELEGATED ; 
 int ZIO_FLAG_DONT_RETRY ; 
 int ZIO_STAGE_VDEV_IO_START ; 
 int /*<<< orphan*/  ZIO_VDEV_CHILD_PIPELINE ; 
 int /*<<< orphan*/ * zio_create (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 

zio_t *
zio_vdev_delegated_io(vdev_t *vd, uint64_t offset, abd_t *data, uint64_t size,
    zio_type_t type, zio_priority_t priority, enum zio_flag flags,
    zio_done_func_t *done, void *private)
{
	zio_t *zio;

	ASSERT(vd->vdev_ops->vdev_op_leaf);

	zio = zio_create(NULL, vd->vdev_spa, 0, NULL,
	    data, size, size, done, private, type, priority,
	    flags | ZIO_FLAG_CANFAIL | ZIO_FLAG_DONT_RETRY | ZIO_FLAG_DELEGATED,
	    vd, offset, NULL,
	    ZIO_STAGE_VDEV_IO_START >> 1, ZIO_VDEV_CHILD_PIPELINE);

	return (zio);
}