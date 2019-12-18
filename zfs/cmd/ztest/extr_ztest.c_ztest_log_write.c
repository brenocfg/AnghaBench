#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  zd_zilog; int /*<<< orphan*/  zd_os; } ;
typedef  TYPE_1__ ztest_ds_t ;
struct TYPE_11__ {scalar_t__ lr_length; int /*<<< orphan*/  lr_common; int /*<<< orphan*/  lr_offset; int /*<<< orphan*/  lr_foid; } ;
typedef  TYPE_2__ lr_write_t ;
typedef  int /*<<< orphan*/  lr_t ;
typedef  scalar_t__ itx_wr_state_t ;
struct TYPE_12__ {int itx_sync; int /*<<< orphan*/  itx_lr; scalar_t__ itx_wr_state; TYPE_1__* itx_private; } ;
typedef  TYPE_3__ itx_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;

/* Variables and functions */
 int /*<<< orphan*/  DMU_READ_NO_PREFETCH ; 
 int /*<<< orphan*/  TX_WRITE ; 
 scalar_t__ WR_COPIED ; 
 scalar_t__ WR_INDIRECT ; 
 scalar_t__ WR_NEED_COPY ; 
 int WR_NUM_STATES ; 
 int /*<<< orphan*/  bcopy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 scalar_t__ dmu_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zil_itx_assign (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_3__* zil_itx_create (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zil_itx_destroy (TYPE_3__*) ; 
 scalar_t__ zil_max_log_data (int /*<<< orphan*/ ) ; 
 scalar_t__ zil_replaying (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ ztest_random (int) ; 

__attribute__((used)) static void
ztest_log_write(ztest_ds_t *zd, dmu_tx_t *tx, lr_write_t *lr)
{
	itx_t *itx;
	itx_wr_state_t write_state = ztest_random(WR_NUM_STATES);

	if (zil_replaying(zd->zd_zilog, tx))
		return;

	if (lr->lr_length > zil_max_log_data(zd->zd_zilog))
		write_state = WR_INDIRECT;

	itx = zil_itx_create(TX_WRITE,
	    sizeof (*lr) + (write_state == WR_COPIED ? lr->lr_length : 0));

	if (write_state == WR_COPIED &&
	    dmu_read(zd->zd_os, lr->lr_foid, lr->lr_offset, lr->lr_length,
	    ((lr_write_t *)&itx->itx_lr) + 1, DMU_READ_NO_PREFETCH) != 0) {
		zil_itx_destroy(itx);
		itx = zil_itx_create(TX_WRITE, sizeof (*lr));
		write_state = WR_NEED_COPY;
	}
	itx->itx_private = zd;
	itx->itx_wr_state = write_state;
	itx->itx_sync = (ztest_random(8) == 0);

	bcopy(&lr->lr_common + 1, &itx->itx_lr + 1,
	    sizeof (*lr) - sizeof (lr_t));

	zil_itx_assign(zd->zd_zilog, itx, tx);
}