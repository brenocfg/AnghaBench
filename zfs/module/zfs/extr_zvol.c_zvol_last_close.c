#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * zv_objset; int /*<<< orphan*/  zv_state_lock; int /*<<< orphan*/  zv_suspend_lock; } ;
typedef  TYPE_1__ zvol_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_READ_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_disown (int /*<<< orphan*/ *,int,TYPE_1__*) ; 
 int /*<<< orphan*/  zvol_shutdown_zv (TYPE_1__*) ; 

void
zvol_last_close(zvol_state_t *zv)
{
	ASSERT(RW_READ_HELD(&zv->zv_suspend_lock));
	ASSERT(MUTEX_HELD(&zv->zv_state_lock));

	zvol_shutdown_zv(zv);

	dmu_objset_disown(zv->zv_objset, 1, zv);
	zv->zv_objset = NULL;
}