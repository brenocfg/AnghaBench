#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  zo_lock; } ;
typedef  TYPE_1__ zfs_onexit_t ;
struct TYPE_7__ {void* za_data; } ;
typedef  TYPE_2__ zfs_onexit_action_node_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  minor_t ;

/* Variables and functions */
 int /*<<< orphan*/  ENOENT ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 TYPE_2__* zfs_onexit_find_cb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int zfs_onexit_minor_to_state (int /*<<< orphan*/ ,TYPE_1__**) ; 

int
zfs_onexit_cb_data(minor_t minor, uint64_t action_handle, void **data)
{
	zfs_onexit_t *zo;
	zfs_onexit_action_node_t *ap;
	int error;

	*data = NULL;

	error = zfs_onexit_minor_to_state(minor, &zo);
	if (error)
		return (error);

	mutex_enter(&zo->zo_lock);
	ap = zfs_onexit_find_cb(zo, action_handle);
	if (ap != NULL)
		*data = ap->za_data;
	else
		error = SET_ERROR(ENOENT);
	mutex_exit(&zo->zo_lock);

	return (error);
}