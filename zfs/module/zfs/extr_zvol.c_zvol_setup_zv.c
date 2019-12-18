#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int zv_volsize; int /*<<< orphan*/  zv_flags; int /*<<< orphan*/  zv_dn; int /*<<< orphan*/  zv_name; int /*<<< orphan*/ * zv_zilog; int /*<<< orphan*/  zv_suspend_lock; int /*<<< orphan*/  zv_state_lock; int /*<<< orphan*/ * zv_objset; } ;
typedef  TYPE_1__ zvol_state_t ;
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_8__ {int /*<<< orphan*/  (* zv_set_disk_ro ) (TYPE_1__*,int) ;int /*<<< orphan*/  (* zv_set_capacity ) (TYPE_1__*,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  RW_LOCK_HELD (int /*<<< orphan*/ *) ; 
 int SET_ERROR (int) ; 
 int /*<<< orphan*/  ZVOL_OBJ ; 
 int /*<<< orphan*/  ZVOL_RDONLY ; 
 int /*<<< orphan*/  ZVOL_WRITTEN_TO ; 
 int /*<<< orphan*/  ZVOL_ZAP_OBJ ; 
 scalar_t__ dmu_objset_is_snapshot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_objset_spa (int /*<<< orphan*/ *) ; 
 int dnode_hold (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int dsl_prop_get_integer (int /*<<< orphan*/ ,char*,int*,int /*<<< orphan*/ *) ; 
 TYPE_6__* ops ; 
 int /*<<< orphan*/  spa_writeable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*,int) ; 
 int /*<<< orphan*/  stub3 (TYPE_1__*,int) ; 
 int zap_lookup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int,int*) ; 

__attribute__((used)) static int
zvol_setup_zv(zvol_state_t *zv)
{
	uint64_t volsize;
	int error;
	uint64_t ro;
	objset_t *os = zv->zv_objset;

	ASSERT(MUTEX_HELD(&zv->zv_state_lock));
	ASSERT(RW_LOCK_HELD(&zv->zv_suspend_lock));

	zv->zv_zilog = NULL;
	zv->zv_flags &= ~ZVOL_WRITTEN_TO;

	error = dsl_prop_get_integer(zv->zv_name, "readonly", &ro, NULL);
	if (error)
		return (SET_ERROR(error));

	error = zap_lookup(os, ZVOL_ZAP_OBJ, "size", 8, 1, &volsize);
	if (error)
		return (SET_ERROR(error));

	error = dnode_hold(os, ZVOL_OBJ, FTAG, &zv->zv_dn);
	if (error)
		return (SET_ERROR(error));

	ops->zv_set_capacity(zv, volsize >> 9);
	zv->zv_volsize = volsize;

	if (ro || dmu_objset_is_snapshot(os) ||
	    !spa_writeable(dmu_objset_spa(os))) {
		ops->zv_set_disk_ro(zv, 1);
		zv->zv_flags |= ZVOL_RDONLY;
	} else {
		ops->zv_set_disk_ro(zv, 0);
		zv->zv_flags &= ~ZVOL_RDONLY;
	}
	return (0);
}