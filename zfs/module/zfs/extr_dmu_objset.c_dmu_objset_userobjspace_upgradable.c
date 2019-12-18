#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  objset_t ;
typedef  int boolean_t ;

/* Variables and functions */
 scalar_t__ DMU_OST_ZFS ; 
 int /*<<< orphan*/  dmu_objset_is_snapshot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_spa (int /*<<< orphan*/ *) ; 
 scalar_t__ dmu_objset_type (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_userobjspace_present (int /*<<< orphan*/ *) ; 
 scalar_t__ dmu_objset_userobjused_enabled (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_writeable (int /*<<< orphan*/ ) ; 

boolean_t
dmu_objset_userobjspace_upgradable(objset_t *os)
{
	return (dmu_objset_type(os) == DMU_OST_ZFS &&
	    !dmu_objset_is_snapshot(os) &&
	    dmu_objset_userobjused_enabled(os) &&
	    !dmu_objset_userobjspace_present(os) &&
	    spa_writeable(dmu_objset_spa(os)));
}