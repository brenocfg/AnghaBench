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
struct TYPE_6__ {int /*<<< orphan*/  io_error; TYPE_1__* io_vd; } ;
typedef  TYPE_2__ zio_t ;
struct TYPE_7__ {int /*<<< orphan*/  vf_vnode; } ;
typedef  TYPE_3__ vdev_file_t ;
struct TYPE_5__ {TYPE_3__* vdev_tsd; } ;

/* Variables and functions */
 int FDSYNC ; 
 int FSYNC ; 
 int /*<<< orphan*/  VOP_FSYNC (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kcred ; 
 int /*<<< orphan*/  zio_interrupt (TYPE_2__*) ; 

__attribute__((used)) static void
vdev_file_io_fsync(void *arg)
{
	zio_t *zio = (zio_t *)arg;
	vdev_file_t *vf = zio->io_vd->vdev_tsd;

	zio->io_error = VOP_FSYNC(vf->vf_vnode, FSYNC | FDSYNC, kcred, NULL);

	zio_interrupt(zio);
}