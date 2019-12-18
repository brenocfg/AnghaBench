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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  objset_t ;
typedef  enum dmu_tx_hold_type { ____Placeholder_dmu_tx_hold_type } dmu_tx_hold_type ;
typedef  int /*<<< orphan*/  dnode_t ;
struct TYPE_4__ {int tx_err; } ;
typedef  TYPE_1__ dmu_tx_t ;
typedef  int /*<<< orphan*/  dmu_tx_hold_t ;

/* Variables and functions */
 scalar_t__ DMU_NEW_OBJECT ; 
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/ * dmu_tx_hold_dnode_impl (TYPE_1__*,int /*<<< orphan*/ *,int,scalar_t__,scalar_t__) ; 
 int dnode_hold (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  dnode_rele (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static dmu_tx_hold_t *
dmu_tx_hold_object_impl(dmu_tx_t *tx, objset_t *os, uint64_t object,
    enum dmu_tx_hold_type type, uint64_t arg1, uint64_t arg2)
{
	dnode_t *dn = NULL;
	dmu_tx_hold_t *txh;
	int err;

	if (object != DMU_NEW_OBJECT) {
		err = dnode_hold(os, object, FTAG, &dn);
		if (err != 0) {
			tx->tx_err = err;
			return (NULL);
		}
	}
	txh = dmu_tx_hold_dnode_impl(tx, dn, type, arg1, arg2);
	if (dn != NULL)
		dnode_rele(dn, FTAG);
	return (txh);
}