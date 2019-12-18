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
struct TYPE_5__ {scalar_t__ zv_open_count; int /*<<< orphan*/  zv_state_lock; int /*<<< orphan*/  zv_suspend_ref; int /*<<< orphan*/  zv_suspend_lock; } ;
typedef  TYPE_1__ zvol_state_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  RW_WRITE_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 TYPE_1__* zvol_find_by_name (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_shutdown_zv (TYPE_1__*) ; 

zvol_state_t *
zvol_suspend(const char *name)
{
	zvol_state_t *zv;

	zv = zvol_find_by_name(name, RW_WRITER);

	if (zv == NULL)
		return (NULL);

	/* block all I/O, release in zvol_resume. */
	ASSERT(MUTEX_HELD(&zv->zv_state_lock));
	ASSERT(RW_WRITE_HELD(&zv->zv_suspend_lock));

	atomic_inc(&zv->zv_suspend_ref);

	if (zv->zv_open_count > 0)
		zvol_shutdown_zv(zv);

	/*
	 * do not hold zv_state_lock across suspend/resume to
	 * avoid locking up zvol lookups
	 */
	mutex_exit(&zv->zv_state_lock);

	/* zv_suspend_lock is released in zvol_resume() */
	return (zv);
}