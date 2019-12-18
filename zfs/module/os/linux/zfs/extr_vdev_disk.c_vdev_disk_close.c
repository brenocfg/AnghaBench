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
struct TYPE_5__ {TYPE_2__* vdev_tsd; int /*<<< orphan*/  vdev_spa; scalar_t__ vdev_reopening; } ;
typedef  TYPE_1__ vdev_t ;
struct TYPE_6__ {int /*<<< orphan*/  vd_lock; int /*<<< orphan*/ * vd_bdev; } ;
typedef  TYPE_2__ vdev_disk_t ;

/* Variables and functions */
 int FMODE_EXCL ; 
 int /*<<< orphan*/  blkdev_put (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_mode (int /*<<< orphan*/ ) ; 
 int vdev_bdev_mode (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
vdev_disk_close(vdev_t *v)
{
	vdev_disk_t *vd = v->vdev_tsd;

	if (v->vdev_reopening || vd == NULL)
		return;

	if (vd->vd_bdev != NULL) {
		blkdev_put(vd->vd_bdev,
		    vdev_bdev_mode(spa_mode(v->vdev_spa)) | FMODE_EXCL);
	}

	rw_destroy(&vd->vd_lock);
	kmem_free(vd, sizeof (vdev_disk_t));
	v->vdev_tsd = NULL;
}