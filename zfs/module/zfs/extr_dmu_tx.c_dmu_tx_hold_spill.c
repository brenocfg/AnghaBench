#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_6__ {int /*<<< orphan*/  tx_objset; } ;
typedef  TYPE_1__ dmu_tx_t ;
struct TYPE_7__ {int /*<<< orphan*/  txh_space_towrite; } ;
typedef  TYPE_2__ dmu_tx_hold_t ;

/* Variables and functions */
 int /*<<< orphan*/  FTAG ; 
 int /*<<< orphan*/  SPA_OLD_MAXBLOCKSIZE ; 
 int /*<<< orphan*/  THT_SPILL ; 
 TYPE_2__* dmu_tx_hold_object_impl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zfs_refcount_add_many (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dmu_tx_hold_spill(dmu_tx_t *tx, uint64_t object)
{
	dmu_tx_hold_t *txh;

	txh = dmu_tx_hold_object_impl(tx, tx->tx_objset, object,
	    THT_SPILL, 0, 0);
	if (txh != NULL)
		(void) zfs_refcount_add_many(&txh->txh_space_towrite,
		    SPA_OLD_MAXBLOCKSIZE, FTAG);
}