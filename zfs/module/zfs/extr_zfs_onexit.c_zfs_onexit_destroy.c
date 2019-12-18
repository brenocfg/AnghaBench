#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  zo_lock; int /*<<< orphan*/  zo_actions; int /*<<< orphan*/  za_data; int /*<<< orphan*/  (* za_func ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ zfs_onexit_t ;
typedef  TYPE_1__ zfs_onexit_action_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void
zfs_onexit_destroy(zfs_onexit_t *zo)
{
	zfs_onexit_action_node_t *ap;

	mutex_enter(&zo->zo_lock);
	while ((ap = list_head(&zo->zo_actions)) != NULL) {
		list_remove(&zo->zo_actions, ap);
		mutex_exit(&zo->zo_lock);
		ap->za_func(ap->za_data);
		kmem_free(ap, sizeof (zfs_onexit_action_node_t));
		mutex_enter(&zo->zo_lock);
	}
	mutex_exit(&zo->zo_lock);

	list_destroy(&zo->zo_actions);
	mutex_destroy(&zo->zo_lock);
	kmem_free(zo, sizeof (zfs_onexit_t));
}