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
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ zv_open_count; struct TYPE_6__* zv_zso; int /*<<< orphan*/  zvo_kstat; int /*<<< orphan*/  zv_state_lock; int /*<<< orphan*/  zvo_dev; TYPE_3__* zvo_disk; int /*<<< orphan*/  zvo_queue; int /*<<< orphan*/  zv_rangelock; int /*<<< orphan*/  zv_suspend_lock; } ;
typedef  TYPE_1__ zvol_state_t ;
struct zvol_state_os {int dummy; } ;
struct TYPE_7__ {int /*<<< orphan*/ * private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int MINOR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_LOCK_HELD (int /*<<< orphan*/ *) ; 
 int ZVOL_MINOR_BITS ; 
 int /*<<< orphan*/  blk_cleanup_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dataset_kstats_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_gendisk (TYPE_3__*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  put_disk (TYPE_3__*) ; 
 int /*<<< orphan*/  rw_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_rangelock_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zvol_ida ; 

__attribute__((used)) static void
zvol_free(zvol_state_t *zv)
{

	ASSERT(!RW_LOCK_HELD(&zv->zv_suspend_lock));
	ASSERT(!MUTEX_HELD(&zv->zv_state_lock));
	ASSERT(zv->zv_open_count == 0);
	ASSERT(zv->zv_zso->zvo_disk->private_data == NULL);

	rw_destroy(&zv->zv_suspend_lock);
	zfs_rangelock_fini(&zv->zv_rangelock);

	del_gendisk(zv->zv_zso->zvo_disk);
	blk_cleanup_queue(zv->zv_zso->zvo_queue);
	put_disk(zv->zv_zso->zvo_disk);

	ida_simple_remove(&zvol_ida,
	    MINOR(zv->zv_zso->zvo_dev) >> ZVOL_MINOR_BITS);

	mutex_destroy(&zv->zv_state_lock);
	dataset_kstats_destroy(&zv->zv_zso->zvo_kstat);

	kmem_free(zv->zv_zso, sizeof (struct zvol_state_os));
	kmem_free(zv, sizeof (zvol_state_t));
}