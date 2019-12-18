#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zilog_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  blk_birth; } ;
struct TYPE_6__ {TYPE_5__ lr_blkptr; } ;
typedef  TYPE_1__ lr_write_t ;
struct TYPE_7__ {scalar_t__ lrc_txtype; } ;
typedef  TYPE_2__ lr_t ;

/* Variables and functions */
 scalar_t__ TX_WRITE ; 
 int zil_claim_log_block (int /*<<< orphan*/ *,TYPE_5__*,void*,int /*<<< orphan*/ ) ; 
 int zil_read_log_data (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
zil_claim_log_record(zilog_t *zilog, lr_t *lrc, void *tx, uint64_t first_txg)
{
	lr_write_t *lr = (lr_write_t *)lrc;
	int error;

	if (lrc->lrc_txtype != TX_WRITE)
		return (0);

	/*
	 * If the block is not readable, don't claim it.  This can happen
	 * in normal operation when a log block is written to disk before
	 * some of the dmu_sync() blocks it points to.  In this case, the
	 * transaction cannot have been committed to anyone (we would have
	 * waited for all writes to be stable first), so it is semantically
	 * correct to declare this the end of the log.
	 */
	if (lr->lr_blkptr.blk_birth >= first_txg) {
		error = zil_read_log_data(zilog, lr, NULL);
		if (error != 0)
			return (error);
	}

	return (zil_claim_log_block(zilog, &lr->lr_blkptr, tx, first_txg));
}