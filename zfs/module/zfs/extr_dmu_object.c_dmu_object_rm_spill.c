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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
struct TYPE_8__ {int /*<<< orphan*/  dn_struct_rwlock; TYPE_1__* dn_phys; } ;
typedef  TYPE_2__ dnode_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_7__ {int dn_flags; } ;

/* Variables and functions */
 int DNODE_FLAG_SPILL_BLKPTR ; 
 int /*<<< orphan*/  DNODE_MUST_BE_ALLOCATED ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int /*<<< orphan*/  dbuf_rm_spill (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int dnode_hold_impl (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  dnode_rele (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dnode_rm_spill (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 

int
dmu_object_rm_spill(objset_t *os, uint64_t object, dmu_tx_t *tx)
{
	dnode_t *dn;
	int err;

	err = dnode_hold_impl(os, object, DNODE_MUST_BE_ALLOCATED, 0,
	    FTAG, &dn);
	if (err)
		return (err);

	rw_enter(&dn->dn_struct_rwlock, RW_WRITER);
	if (dn->dn_phys->dn_flags & DNODE_FLAG_SPILL_BLKPTR) {
		dbuf_rm_spill(dn, tx);
		dnode_rm_spill(dn, tx);
	}
	rw_exit(&dn->dn_struct_rwlock);

	dnode_rele(dn, FTAG);
	return (err);
}