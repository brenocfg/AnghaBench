#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int zs_minor; int /*<<< orphan*/  zs_zevent; int /*<<< orphan*/  zs_onexit; } ;
typedef  TYPE_1__ zfsdev_state_t ;
struct file {TYPE_1__* private_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zfs_onexit_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_zevent_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfsdev_state_lock ; 

__attribute__((used)) static int
zfsdev_state_destroy(struct file *filp)
{
	zfsdev_state_t *zs;

	ASSERT(MUTEX_HELD(&zfsdev_state_lock));
	ASSERT(filp->private_data != NULL);

	zs = filp->private_data;
	zs->zs_minor = -1;
	zfs_onexit_destroy(zs->zs_onexit);
	zfs_zevent_destroy(zs->zs_zevent);

	return (0);
}