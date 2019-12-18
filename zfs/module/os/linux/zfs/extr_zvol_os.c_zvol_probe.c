#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  zv_state_lock; TYPE_1__* zv_zso; } ;
typedef  TYPE_2__ zvol_state_t ;
struct kobject {int dummy; } ;
typedef  int /*<<< orphan*/  dev_t ;
struct TYPE_4__ {int /*<<< orphan*/  zvo_disk; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ MUTEX_HELD (int /*<<< orphan*/ *) ; 
 struct kobject* get_disk_and_module (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 TYPE_2__* zvol_find_by_dev (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct kobject *
zvol_probe(dev_t dev, int *part, void *arg)
{
	zvol_state_t *zv;
	struct kobject *kobj;

	zv = zvol_find_by_dev(dev);
	kobj = zv ? get_disk_and_module(zv->zv_zso->zvo_disk) : NULL;
	ASSERT(zv == NULL || MUTEX_HELD(&zv->zv_state_lock));
	if (zv)
		mutex_exit(&zv->zv_state_lock);

	return (kobj);
}