#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ tx_quiescing_txg; int /*<<< orphan*/  tx_sync_lock; } ;
typedef  TYPE_1__ tx_state_t ;
struct TYPE_5__ {TYPE_1__ dp_tx; } ;
typedef  TYPE_2__ dsl_pool_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 

__attribute__((used)) static boolean_t
txg_is_quiescing(dsl_pool_t *dp)
{
	tx_state_t *tx = &dp->dp_tx;
	ASSERT(MUTEX_HELD(&tx->tx_sync_lock));
	return (tx->tx_quiescing_txg != 0);
}