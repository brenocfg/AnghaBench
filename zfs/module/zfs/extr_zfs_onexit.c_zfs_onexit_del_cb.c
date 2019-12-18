#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  zo_lock; int /*<<< orphan*/  zo_actions; } ;
typedef  TYPE_1__ zfs_onexit_t ;
struct TYPE_9__ {int /*<<< orphan*/  za_data; int /*<<< orphan*/  (* za_func ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_2__ zfs_onexit_action_node_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  minor_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 TYPE_2__* zfs_onexit_find_cb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int zfs_onexit_minor_to_state (int /*<<< orphan*/ ,TYPE_1__**) ; 

int
zfs_onexit_del_cb(minor_t minor, uint64_t action_handle, boolean_t fire)
{
	zfs_onexit_t *zo;
	zfs_onexit_action_node_t *ap;
	int error;

	error = zfs_onexit_minor_to_state(minor, &zo);
	if (error)
		return (error);

	mutex_enter(&zo->zo_lock);
	ap = zfs_onexit_find_cb(zo, action_handle);
	if (ap != NULL) {
		list_remove(&zo->zo_actions, ap);
		mutex_exit(&zo->zo_lock);
		if (fire)
			ap->za_func(ap->za_data);
		kmem_free(ap, sizeof (zfs_onexit_action_node_t));
	} else {
		mutex_exit(&zo->zo_lock);
		error = SET_ERROR(ENOENT);
	}

	return (error);
}