#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  spa_t ;
struct TYPE_6__ {TYPE_1__* tx_pool; int /*<<< orphan*/  tx_txg; } ;
typedef  TYPE_2__ dmu_tx_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
struct TYPE_5__ {int /*<<< orphan*/  dp_free_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  BP_GET_PSIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  BP_GET_UCSIZE (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  DD_USED_HEAD ; 
 int /*<<< orphan*/  bp_get_dsize_sync (int /*<<< orphan*/ *,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  dsl_dir_diduse_space (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  zio_free (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static int
delete_blkptr_cb(void *arg, const blkptr_t *bp, dmu_tx_t *tx)
{
	spa_t *spa = arg;
	zio_free(spa, tx->tx_txg, bp);
	dsl_dir_diduse_space(tx->tx_pool->dp_free_dir, DD_USED_HEAD,
	    -bp_get_dsize_sync(spa, bp),
	    -BP_GET_PSIZE(bp), -BP_GET_UCSIZE(bp), tx);
	return (0);
}