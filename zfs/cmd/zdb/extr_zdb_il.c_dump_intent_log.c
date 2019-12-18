#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_2__* zl_spa; TYPE_4__* zl_header; } ;
typedef  TYPE_3__ zilog_t ;
struct TYPE_11__ {scalar_t__ zh_claim_txg; scalar_t__ zh_flags; scalar_t__ zh_replay_seq; scalar_t__ zh_claim_lr_seq; scalar_t__ zh_claim_blk_seq; int /*<<< orphan*/  zh_log; } ;
typedef  TYPE_4__ zil_header_t ;
typedef  int /*<<< orphan*/  u_longlong_t ;
struct TYPE_12__ {scalar_t__ zri_count; } ;
struct TYPE_8__ {scalar_t__ ub_checkpoint_txg; } ;
struct TYPE_9__ {TYPE_1__ spa_uberblock; } ;

/* Variables and functions */
 scalar_t__ BP_IS_HOLE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int MAX (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int TX_MAX_TYPE ; 
 int /*<<< orphan*/ * dump_opt ; 
 int /*<<< orphan*/  print_log_block ; 
 int /*<<< orphan*/  print_log_record ; 
 int /*<<< orphan*/  print_log_stats (int) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  zil_parse (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 TYPE_5__* zil_rec_info ; 

void
dump_intent_log(zilog_t *zilog)
{
	const zil_header_t *zh = zilog->zl_header;
	int verbose = MAX(dump_opt['d'], dump_opt['i']);
	int i;

	if (BP_IS_HOLE(&zh->zh_log) || verbose < 1)
		return;

	(void) printf("\n    ZIL header: claim_txg %llu, "
	    "claim_blk_seq %llu, claim_lr_seq %llu",
	    (u_longlong_t)zh->zh_claim_txg,
	    (u_longlong_t)zh->zh_claim_blk_seq,
	    (u_longlong_t)zh->zh_claim_lr_seq);
	(void) printf(" replay_seq %llu, flags 0x%llx\n",
	    (u_longlong_t)zh->zh_replay_seq, (u_longlong_t)zh->zh_flags);

	for (i = 0; i < TX_MAX_TYPE; i++)
		zil_rec_info[i].zri_count = 0;

	/* see comment in zil_claim() or zil_check_log_chain() */
	if (zilog->zl_spa->spa_uberblock.ub_checkpoint_txg != 0 &&
	    zh->zh_claim_txg == 0)
		return;

	if (verbose >= 2) {
		(void) printf("\n");
		(void) zil_parse(zilog, print_log_block, print_log_record, NULL,
		    zh->zh_claim_txg, B_FALSE);
		print_log_stats(verbose);
	}
}