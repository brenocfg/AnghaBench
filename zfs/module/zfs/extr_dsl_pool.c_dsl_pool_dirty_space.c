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
typedef  scalar_t__ int64_t ;
struct TYPE_6__ {int /*<<< orphan*/  dp_lock; int /*<<< orphan*/ * dp_dirty_pertxg; } ;
typedef  TYPE_1__ dsl_pool_t ;
struct TYPE_7__ {size_t tx_txg; } ;
typedef  TYPE_2__ dmu_tx_t ;

/* Variables and functions */
 size_t TXG_MASK ; 
 int /*<<< orphan*/  dsl_pool_dirty_delta (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
dsl_pool_dirty_space(dsl_pool_t *dp, int64_t space, dmu_tx_t *tx)
{
	if (space > 0) {
		mutex_enter(&dp->dp_lock);
		dp->dp_dirty_pertxg[tx->tx_txg & TXG_MASK] += space;
		dsl_pool_dirty_delta(dp, space);
		mutex_exit(&dp->dp_lock);
	}
}