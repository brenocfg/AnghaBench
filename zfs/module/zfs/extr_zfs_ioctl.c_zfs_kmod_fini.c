#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* zs_next; } ;
typedef  TYPE_1__ zfsdev_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rrw_tsd_key ; 
 int /*<<< orphan*/  spa_fini () ; 
 int /*<<< orphan*/  tsd_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_allow_log_key ; 
 int /*<<< orphan*/  zfs_fini () ; 
 int /*<<< orphan*/  zfs_fsyncer_key ; 
 int /*<<< orphan*/  zfsdev_detach () ; 
 TYPE_1__* zfsdev_state_list ; 
 int /*<<< orphan*/  zfsdev_state_lock ; 
 int /*<<< orphan*/  zvol_fini () ; 

void
zfs_kmod_fini(void)
{
	zfsdev_state_t *zs, *zsprev = NULL;

	zfsdev_detach();

	mutex_destroy(&zfsdev_state_lock);

	for (zs = zfsdev_state_list; zs != NULL; zs = zs->zs_next) {
		if (zsprev)
			kmem_free(zsprev, sizeof (zfsdev_state_t));
		zsprev = zs;
	}
	if (zsprev)
		kmem_free(zsprev, sizeof (zfsdev_state_t));

	zfs_fini();
	spa_fini();
	zvol_fini();

	tsd_destroy(&zfs_fsyncer_key);
	tsd_destroy(&rrw_tsd_key);
	tsd_destroy(&zfs_allow_log_key);
}