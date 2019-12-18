#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int vdev_children; int /*<<< orphan*/  vdev_path; int /*<<< orphan*/  vdev_wholedisk; TYPE_1__* vdev_ops; struct TYPE_9__** vdev_child; TYPE_4__* vdev_tsd; } ;
typedef  TYPE_3__ vdev_t ;
struct TYPE_10__ {TYPE_6__* vd_bdev; } ;
typedef  TYPE_4__ vdev_disk_t ;
struct request_queue {int dummy; } ;
struct TYPE_11__ {TYPE_2__* bd_disk; } ;
struct TYPE_8__ {char* disk_name; } ;
struct TYPE_7__ {int /*<<< orphan*/  vdev_op_leaf; } ;

/* Variables and functions */
 int /*<<< orphan*/  SET_SCHEDULER_CMD ; 
 int /*<<< orphan*/  UMH_NO_WAIT ; 
 struct request_queue* bdev_get_queue (TYPE_6__*) ; 
 int call_usermodehelper (char*,char**,char**,int /*<<< orphan*/ ) ; 
 int elevator_change (struct request_queue*,char*) ; 
 char* kmem_asprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  kmem_strfree (char*) ; 
 int strlen (char*) ; 
 scalar_t__ strncmp (char*,char*,int) ; 
 int /*<<< orphan*/  zfs_dbgmsg (char*,char*,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void
vdev_elevator_switch(vdev_t *v, char *elevator)
{
	vdev_disk_t *vd = v->vdev_tsd;
	struct request_queue *q;
	char *device;
	int error;

	for (int c = 0; c < v->vdev_children; c++)
		vdev_elevator_switch(v->vdev_child[c], elevator);

	if (!v->vdev_ops->vdev_op_leaf || vd->vd_bdev == NULL)
		return;

	q = bdev_get_queue(vd->vd_bdev);
	device = vd->vd_bdev->bd_disk->disk_name;

	/*
	 * Skip devices which are not whole disks (partitions).
	 * Device-mapper devices are excepted since they may be whole
	 * disks despite the vdev_wholedisk flag, in which case we can
	 * and should switch the elevator. If the device-mapper device
	 * does not have an elevator (i.e. dm-raid, dm-crypt, etc.) the
	 * "Skip devices without schedulers" check below will fail.
	 */
	if (!v->vdev_wholedisk && strncmp(device, "dm-", 3) != 0)
		return;

	/* Leave existing scheduler when set to "none" */
	if ((strncmp(elevator, "none", 4) == 0) && (strlen(elevator) == 4))
		return;

	/*
	 * The elevator_change() function was available in kernels from
	 * 2.6.36 to 4.11.  When not available fall back to using the user
	 * mode helper functionality to set the elevator via sysfs.  This
	 * requires /bin/echo and sysfs to be mounted which may not be true
	 * early in the boot process.
	 */
#ifdef HAVE_ELEVATOR_CHANGE
	error = elevator_change(q, elevator);
#else
#define	SET_SCHEDULER_CMD \
	"exec 0</dev/null " \
	"     1>/sys/block/%s/queue/scheduler " \
	"     2>/dev/null; " \
	"echo %s"

	char *argv[] = { "/bin/sh", "-c", NULL, NULL };
	char *envp[] = { NULL };

	argv[2] = kmem_asprintf(SET_SCHEDULER_CMD, device, elevator);
	error = call_usermodehelper(argv[0], argv, envp, UMH_NO_WAIT);
	kmem_strfree(argv[2]);
#endif /* HAVE_ELEVATOR_CHANGE */
	if (error) {
		zfs_dbgmsg("Unable to set \"%s\" scheduler for %s (%s): %d",
		    elevator, v->vdev_path, device, error);
	}
}