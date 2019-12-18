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
struct TYPE_6__ {int /*<<< orphan*/  zo_lock; int /*<<< orphan*/  zo_actions; } ;
typedef  TYPE_1__ zfs_onexit_t ;
struct TYPE_7__ {void (* za_func ) (void*) ;void* za_data; int /*<<< orphan*/  za_link; } ;
typedef  TYPE_2__ zfs_onexit_action_node_t ;
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  minor_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 TYPE_2__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_insert_tail (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  list_link_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int zfs_onexit_minor_to_state (int /*<<< orphan*/ ,TYPE_1__**) ; 

int
zfs_onexit_add_cb(minor_t minor, void (*func)(void *), void *data,
    uint64_t *action_handle)
{
	zfs_onexit_t *zo;
	zfs_onexit_action_node_t *ap;
	int error;

	error = zfs_onexit_minor_to_state(minor, &zo);
	if (error)
		return (error);

	ap = kmem_alloc(sizeof (zfs_onexit_action_node_t), KM_SLEEP);
	list_link_init(&ap->za_link);
	ap->za_func = func;
	ap->za_data = data;

	mutex_enter(&zo->zo_lock);
	list_insert_tail(&zo->zo_actions, ap);
	mutex_exit(&zo->zo_lock);
	if (action_handle)
		*action_handle = (uint64_t)(uintptr_t)ap;

	return (0);
}