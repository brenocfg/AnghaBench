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
struct TYPE_4__ {int zs_minor; struct TYPE_4__* zs_next; int /*<<< orphan*/  zs_zevent; int /*<<< orphan*/  zs_onexit; struct file* zs_file; } ;
typedef  TYPE_1__ zfsdev_state_t ;
typedef  int /*<<< orphan*/  zfs_zevent_t ;
typedef  int /*<<< orphan*/  zfs_onexit_t ;
struct file {TYPE_1__* private_data; } ;
typedef  void* minor_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ B_FALSE ; 
 scalar_t__ B_TRUE ; 
 int /*<<< orphan*/  ENXIO ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 TYPE_1__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smp_wmb () ; 
 int /*<<< orphan*/  zfs_onexit_init (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zfs_zevent_init (int /*<<< orphan*/ **) ; 
 void* zfsdev_minor_alloc () ; 
 TYPE_1__* zfsdev_state_list ; 
 int /*<<< orphan*/  zfsdev_state_lock ; 

__attribute__((used)) static int
zfsdev_state_init(struct file *filp)
{
	zfsdev_state_t *zs, *zsprev = NULL;
	minor_t minor;
	boolean_t newzs = B_FALSE;

	ASSERT(MUTEX_HELD(&zfsdev_state_lock));

	minor = zfsdev_minor_alloc();
	if (minor == 0)
		return (SET_ERROR(ENXIO));

	for (zs = zfsdev_state_list; zs != NULL; zs = zs->zs_next) {
		if (zs->zs_minor == -1)
			break;
		zsprev = zs;
	}

	if (!zs) {
		zs = kmem_zalloc(sizeof (zfsdev_state_t), KM_SLEEP);
		newzs = B_TRUE;
	}

	zs->zs_file = filp;
	filp->private_data = zs;

	zfs_onexit_init((zfs_onexit_t **)&zs->zs_onexit);
	zfs_zevent_init((zfs_zevent_t **)&zs->zs_zevent);

	/*
	 * In order to provide for lock-free concurrent read access
	 * to the minor list in zfsdev_get_state_impl(), new entries
	 * must be completely written before linking them into the
	 * list whereas existing entries are already linked; the last
	 * operation must be updating zs_minor (from -1 to the new
	 * value).
	 */
	if (newzs) {
		zs->zs_minor = minor;
		smp_wmb();
		zsprev->zs_next = zs;
	} else {
		smp_wmb();
		zs->zs_minor = minor;
	}

	return (0);
}