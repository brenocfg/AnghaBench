#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zio_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  bplist_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY (int) ; 
 int /*<<< orphan*/  bplist_iterate (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_free_sync_cb ; 
 int /*<<< orphan*/ * zio_root (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zio_wait (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
spa_sync_frees(spa_t *spa, bplist_t *bpl, dmu_tx_t *tx)
{
	zio_t *zio = zio_root(spa, NULL, NULL, 0);
	bplist_iterate(bpl, spa_free_sync_cb, zio, tx);
	VERIFY(zio_wait(zio) == 0);
}