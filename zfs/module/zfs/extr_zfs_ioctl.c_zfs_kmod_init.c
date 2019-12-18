#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zfsdev_state_t ;
struct TYPE_3__ {int zs_minor; } ;

/* Variables and functions */
 int FREAD ; 
 int FWRITE ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MUTEX_DEFAULT ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * rrw_tsd_destroy ; 
 int /*<<< orphan*/  rrw_tsd_key ; 
 int /*<<< orphan*/  spa_fini () ; 
 int /*<<< orphan*/  spa_init (int) ; 
 int /*<<< orphan*/  tsd_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zfs_allow_log_destroy ; 
 int /*<<< orphan*/  zfs_allow_log_key ; 
 int /*<<< orphan*/  zfs_fini () ; 
 int /*<<< orphan*/  zfs_fsyncer_key ; 
 int /*<<< orphan*/  zfs_init () ; 
 int /*<<< orphan*/  zfs_ioctl_init () ; 
 int zfsdev_attach () ; 
 TYPE_1__* zfsdev_state_list ; 
 int /*<<< orphan*/  zfsdev_state_lock ; 
 int /*<<< orphan*/  zvol_fini () ; 
 int zvol_init () ; 

int
zfs_kmod_init(void)
{
	int error;

	if ((error = zvol_init()) != 0)
		return (error);

	spa_init(FREAD | FWRITE);
	zfs_init();

	zfs_ioctl_init();

	mutex_init(&zfsdev_state_lock, NULL, MUTEX_DEFAULT, NULL);
	zfsdev_state_list = kmem_zalloc(sizeof (zfsdev_state_t), KM_SLEEP);
	zfsdev_state_list->zs_minor = -1;

	if ((error = zfsdev_attach()) != 0)
		goto out;

	tsd_create(&zfs_fsyncer_key, NULL);
	tsd_create(&rrw_tsd_key, rrw_tsd_destroy);
	tsd_create(&zfs_allow_log_key, zfs_allow_log_destroy);

	return (0);
out:
	zfs_fini();
	spa_fini();
	zvol_fini();

	return (error);
}