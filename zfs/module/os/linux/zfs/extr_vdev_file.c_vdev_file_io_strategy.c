#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ io_type; scalar_t__ io_error; int /*<<< orphan*/  io_size; int /*<<< orphan*/  io_abd; int /*<<< orphan*/  io_offset; TYPE_2__* io_vd; } ;
typedef  TYPE_1__ zio_t ;
struct TYPE_6__ {TYPE_3__* vdev_tsd; } ;
typedef  TYPE_2__ vdev_t ;
struct TYPE_7__ {int /*<<< orphan*/  vf_vnode; } ;
typedef  TYPE_3__ vdev_file_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOSPC ; 
 int /*<<< orphan*/  RLIM64_INFINITY ; 
 scalar_t__ SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UIO_READ ; 
 int /*<<< orphan*/  UIO_SYSSPACE ; 
 int /*<<< orphan*/  UIO_WRITE ; 
 scalar_t__ ZIO_TYPE_READ ; 
 void* abd_borrow_buf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* abd_borrow_buf_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_return_buf (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  abd_return_buf_copy (int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kcred ; 
 scalar_t__ vn_rdwr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int /*<<< orphan*/  zio_delay_interrupt (TYPE_1__*) ; 

__attribute__((used)) static void
vdev_file_io_strategy(void *arg)
{
	zio_t *zio = (zio_t *)arg;
	vdev_t *vd = zio->io_vd;
	vdev_file_t *vf = vd->vdev_tsd;
	ssize_t resid;
	void *buf;

	if (zio->io_type == ZIO_TYPE_READ)
		buf = abd_borrow_buf(zio->io_abd, zio->io_size);
	else
		buf = abd_borrow_buf_copy(zio->io_abd, zio->io_size);

	zio->io_error = vn_rdwr(zio->io_type == ZIO_TYPE_READ ?
	    UIO_READ : UIO_WRITE, vf->vf_vnode, buf, zio->io_size,
	    zio->io_offset, UIO_SYSSPACE, 0, RLIM64_INFINITY, kcred, &resid);

	if (zio->io_type == ZIO_TYPE_READ)
		abd_return_buf_copy(zio->io_abd, buf, zio->io_size);
	else
		abd_return_buf(zio->io_abd, buf, zio->io_size);

	if (resid != 0 && zio->io_error == 0)
		zio->io_error = SET_ERROR(ENOSPC);

	zio_delay_interrupt(zio);
}