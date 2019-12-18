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
struct dsl_pool {int /*<<< orphan*/  dp_spa; } ;
struct TYPE_4__ {int /*<<< orphan*/  tx_anyobj; int /*<<< orphan*/  tx_txg; struct dsl_pool* tx_pool; } ;
typedef  TYPE_1__ dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TXG_VERIFY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* dmu_tx_create_dd (int /*<<< orphan*/ *) ; 

dmu_tx_t *
dmu_tx_create_assigned(struct dsl_pool *dp, uint64_t txg)
{
	dmu_tx_t *tx = dmu_tx_create_dd(NULL);

	TXG_VERIFY(dp->dp_spa, txg);
	tx->tx_pool = dp;
	tx->tx_txg = txg;
	tx->tx_anyobj = TRUE;

	return (tx);
}