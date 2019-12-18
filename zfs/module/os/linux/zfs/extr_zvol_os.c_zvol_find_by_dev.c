#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  zv_state_lock; TYPE_1__* zv_zso; } ;
typedef  TYPE_2__ zvol_state_t ;
typedef  scalar_t__ dev_t ;
struct TYPE_7__ {scalar_t__ zvo_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  RW_READER ; 
 TYPE_2__* list_head (int /*<<< orphan*/ *) ; 
 TYPE_2__* list_next (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zvol_state_list ; 
 int /*<<< orphan*/  zvol_state_lock ; 

__attribute__((used)) static zvol_state_t *
zvol_find_by_dev(dev_t dev)
{
	zvol_state_t *zv;

	rw_enter(&zvol_state_lock, RW_READER);
	for (zv = list_head(&zvol_state_list); zv != NULL;
	    zv = list_next(&zvol_state_list, zv)) {
		mutex_enter(&zv->zv_state_lock);
		if (zv->zv_zso->zvo_dev == dev) {
			rw_exit(&zvol_state_lock);
			return (zv);
		}
		mutex_exit(&zv->zv_state_lock);
	}
	rw_exit(&zvol_state_lock);

	return (NULL);
}