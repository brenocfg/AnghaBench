#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * z_os; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  int /*<<< orphan*/  objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  dmu_objset_ds (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_is_snapshot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_prop_unregister_all (int /*<<< orphan*/ ,TYPE_1__*) ; 

void
zfs_unregister_callbacks(zfsvfs_t *zfsvfs)
{
	objset_t *os = zfsvfs->z_os;

	if (!dmu_objset_is_snapshot(os))
		dsl_prop_unregister_all(dmu_objset_ds(os), zfsvfs);
}