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
struct TYPE_6__ {int /*<<< orphan*/  zl_dmu_pool; int /*<<< orphan*/  zl_os; int /*<<< orphan*/  zl_spa; int /*<<< orphan*/  zl_destroy_txg; TYPE_2__* zl_header; } ;
typedef  TYPE_1__ zilog_t ;
struct TYPE_7__ {scalar_t__ zh_claim_txg; scalar_t__ zh_replay_seq; int /*<<< orphan*/  zh_log; } ;
typedef  TYPE_2__ zil_header_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  lwb_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  boolean_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  blk ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 scalar_t__ BP_IS_HOLE (int /*<<< orphan*/ *) ; 
 scalar_t__ BP_SHOULD_BYTESWAP (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  BP_ZERO (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  IMPLY (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  TXG_WAIT ; 
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZIL_MIN_BLKSZ ; 
 scalar_t__ bcmp (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dmu_objset_ds (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_assign (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_get_txg (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dsl_dataset_dirty (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  txg_wait_synced (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zil_alloc_lwb (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zil_init_log_chain (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int zio_alloc_zil (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zio_free (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static lwb_t *
zil_create(zilog_t *zilog)
{
	const zil_header_t *zh = zilog->zl_header;
	lwb_t *lwb = NULL;
	uint64_t txg = 0;
	dmu_tx_t *tx = NULL;
	blkptr_t blk;
	int error = 0;
	boolean_t fastwrite = FALSE;
	boolean_t slog = FALSE;

	/*
	 * Wait for any previous destroy to complete.
	 */
	txg_wait_synced(zilog->zl_dmu_pool, zilog->zl_destroy_txg);

	ASSERT(zh->zh_claim_txg == 0);
	ASSERT(zh->zh_replay_seq == 0);

	blk = zh->zh_log;

	/*
	 * Allocate an initial log block if:
	 *    - there isn't one already
	 *    - the existing block is the wrong endianness
	 */
	if (BP_IS_HOLE(&blk) || BP_SHOULD_BYTESWAP(&blk)) {
		tx = dmu_tx_create(zilog->zl_os);
		VERIFY0(dmu_tx_assign(tx, TXG_WAIT));
		dsl_dataset_dirty(dmu_objset_ds(zilog->zl_os), tx);
		txg = dmu_tx_get_txg(tx);

		if (!BP_IS_HOLE(&blk)) {
			zio_free(zilog->zl_spa, txg, &blk);
			BP_ZERO(&blk);
		}

		error = zio_alloc_zil(zilog->zl_spa, zilog->zl_os, txg, &blk,
		    ZIL_MIN_BLKSZ, &slog);
		fastwrite = TRUE;

		if (error == 0)
			zil_init_log_chain(zilog, &blk);
	}

	/*
	 * Allocate a log write block (lwb) for the first log block.
	 */
	if (error == 0)
		lwb = zil_alloc_lwb(zilog, &blk, slog, txg, fastwrite);

	/*
	 * If we just allocated the first log block, commit our transaction
	 * and wait for zil_sync() to stuff the block pointer into zh_log.
	 * (zh is part of the MOS, so we cannot modify it in open context.)
	 */
	if (tx != NULL) {
		dmu_tx_commit(tx);
		txg_wait_synced(zilog->zl_dmu_pool, txg);
	}

	ASSERT(error != 0 || bcmp(&blk, &zh->zh_log, sizeof (blk)) == 0);
	IMPLY(error == 0, lwb != NULL);

	return (lwb);
}