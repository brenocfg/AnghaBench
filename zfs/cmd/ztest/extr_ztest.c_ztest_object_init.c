#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ztest_od_t ;
struct TYPE_6__ {int /*<<< orphan*/  zd_dirobj_lock; int /*<<< orphan*/ * zd_od; } ;
typedef  TYPE_1__ ztest_ds_t ;
typedef  scalar_t__ boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ ztest_create (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ztest_lookup (TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ ztest_remove (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
ztest_object_init(ztest_ds_t *zd, ztest_od_t *od, size_t size, boolean_t remove)
{
	int count = size / sizeof (*od);
	int rv = 0;

	mutex_enter(&zd->zd_dirobj_lock);
	if ((ztest_lookup(zd, od, count) != 0 || remove) &&
	    (ztest_remove(zd, od, count) != 0 ||
	    ztest_create(zd, od, count) != 0))
		rv = -1;
	zd->zd_od = od;
	mutex_exit(&zd->zd_dirobj_lock);

	return (rv);
}