#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int io_cmd; } ;
typedef  TYPE_1__ zio_t ;
typedef  int /*<<< orphan*/  zio_done_func_t ;
struct TYPE_13__ {int vdev_children; struct TYPE_13__** vdev_child; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  enum zio_flag { ____Placeholder_zio_flag } zio_flag ;

/* Variables and functions */
 int /*<<< orphan*/  ZIO_IOCTL_PIPELINE ; 
 int /*<<< orphan*/  ZIO_PRIORITY_NOW ; 
 int /*<<< orphan*/  ZIO_STAGE_OPEN ; 
 int /*<<< orphan*/  ZIO_TYPE_IOCTL ; 
 TYPE_1__* zio_create (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_nowait (TYPE_1__*) ; 
 TYPE_1__* zio_null (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

zio_t *
zio_ioctl(zio_t *pio, spa_t *spa, vdev_t *vd, int cmd,
    zio_done_func_t *done, void *private, enum zio_flag flags)
{
	zio_t *zio;
	int c;

	if (vd->vdev_children == 0) {
		zio = zio_create(pio, spa, 0, NULL, NULL, 0, 0, done, private,
		    ZIO_TYPE_IOCTL, ZIO_PRIORITY_NOW, flags, vd, 0, NULL,
		    ZIO_STAGE_OPEN, ZIO_IOCTL_PIPELINE);

		zio->io_cmd = cmd;
	} else {
		zio = zio_null(pio, spa, NULL, NULL, NULL, flags);

		for (c = 0; c < vd->vdev_children; c++)
			zio_nowait(zio_ioctl(zio, spa, vd->vdev_child[c], cmd,
			    done, private, flags));
	}

	return (zio);
}