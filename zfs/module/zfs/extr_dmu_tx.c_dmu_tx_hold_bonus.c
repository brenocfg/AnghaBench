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
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_4__ {scalar_t__ tx_txg; int /*<<< orphan*/  tx_objset; } ;
typedef  TYPE_1__ dmu_tx_t ;
typedef  int /*<<< orphan*/  dmu_tx_hold_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  THT_BONUS ; 
 int /*<<< orphan*/  dmu_tx_count_dnode (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_hold_object_impl (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void
dmu_tx_hold_bonus(dmu_tx_t *tx, uint64_t object)
{
	dmu_tx_hold_t *txh;

	ASSERT(tx->tx_txg == 0);

	txh = dmu_tx_hold_object_impl(tx, tx->tx_objset,
	    object, THT_BONUS, 0, 0);
	if (txh)
		dmu_tx_count_dnode(txh);
}