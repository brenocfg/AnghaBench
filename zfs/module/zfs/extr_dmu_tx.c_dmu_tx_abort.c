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
struct TYPE_4__ {scalar_t__ tx_txg; int /*<<< orphan*/  tx_callbacks; } ;
typedef  TYPE_1__ dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  ECANCELED ; 
 int /*<<< orphan*/  dmu_tx_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  dmu_tx_do_callbacks (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_is_empty (int /*<<< orphan*/ *) ; 

void
dmu_tx_abort(dmu_tx_t *tx)
{
	ASSERT(tx->tx_txg == 0);

	/*
	 * Call any registered callbacks with an error code.
	 */
	if (!list_is_empty(&tx->tx_callbacks))
		dmu_tx_do_callbacks(&tx->tx_callbacks, ECANCELED);

	dmu_tx_destroy(tx);
}