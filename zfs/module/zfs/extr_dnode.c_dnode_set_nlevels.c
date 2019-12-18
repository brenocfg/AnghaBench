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
struct TYPE_4__ {int dn_nlevels; int /*<<< orphan*/  dn_struct_rwlock; } ;
typedef  TYPE_1__ dnode_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  RW_WRITER ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dnode_set_nlevels_impl (TYPE_1__*,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rw_enter (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rw_exit (int /*<<< orphan*/ *) ; 

int
dnode_set_nlevels(dnode_t *dn, int nlevels, dmu_tx_t *tx)
{
	int ret = 0;

	rw_enter(&dn->dn_struct_rwlock, RW_WRITER);

	if (dn->dn_nlevels == nlevels) {
		ret = 0;
		goto out;
	} else if (nlevels < dn->dn_nlevels) {
		ret = SET_ERROR(EINVAL);
		goto out;
	}

	dnode_set_nlevels_impl(dn, nlevels, tx);

out:
	rw_exit(&dn->dn_struct_rwlock);
	return (ret);
}