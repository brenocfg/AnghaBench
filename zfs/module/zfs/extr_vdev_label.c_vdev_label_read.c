#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  io_spa; } ;
typedef  TYPE_1__ zio_t ;
typedef  int /*<<< orphan*/  zio_done_func_t ;
struct TYPE_8__ {int /*<<< orphan*/  vdev_psize; } ;
typedef  TYPE_2__ vdev_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  abd_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  RW_READER ; 
 int /*<<< orphan*/  RW_WRITER ; 
 scalar_t__ SCL_STATE ; 
 int /*<<< orphan*/  ZIO_CHECKSUM_LABEL ; 
 int ZIO_FLAG_CONFIG_WRITER ; 
 int /*<<< orphan*/  ZIO_PRIORITY_SYNC_READ ; 
 scalar_t__ spa_config_held (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vdev_label_offset (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_nowait (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zio_read_phys (TYPE_1__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vdev_label_read(zio_t *zio, vdev_t *vd, int l, abd_t *buf, uint64_t offset,
    uint64_t size, zio_done_func_t *done, void *private, int flags)
{
	ASSERT(
	    spa_config_held(zio->io_spa, SCL_STATE, RW_READER) == SCL_STATE ||
	    spa_config_held(zio->io_spa, SCL_STATE, RW_WRITER) == SCL_STATE);
	ASSERT(flags & ZIO_FLAG_CONFIG_WRITER);

	zio_nowait(zio_read_phys(zio, vd,
	    vdev_label_offset(vd->vdev_psize, l, offset),
	    size, buf, ZIO_CHECKSUM_LABEL, done, private,
	    ZIO_PRIORITY_SYNC_READ, flags, B_TRUE));
}