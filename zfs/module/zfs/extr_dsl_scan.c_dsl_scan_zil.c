#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zilog_t ;
struct TYPE_8__ {TYPE_2__* member_1; TYPE_3__* member_0; } ;
typedef  TYPE_1__ zil_scan_arg_t ;
struct TYPE_9__ {scalar_t__ zh_claim_txg; } ;
typedef  TYPE_2__ zil_header_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_10__ {int /*<<< orphan*/  dp_meta_objset; int /*<<< orphan*/  dp_spa; } ;
typedef  TYPE_3__ dsl_pool_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  dsl_scan_zil_block ; 
 int /*<<< orphan*/  dsl_scan_zil_record ; 
 int /*<<< orphan*/  spa_writeable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * zil_alloc (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  zil_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zil_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
dsl_scan_zil(dsl_pool_t *dp, zil_header_t *zh)
{
	uint64_t claim_txg = zh->zh_claim_txg;
	zil_scan_arg_t zsa = { dp, zh };
	zilog_t *zilog;

	ASSERT(spa_writeable(dp->dp_spa));

	/*
	 * We only want to visit blocks that have been claimed but not yet
	 * replayed (or, in read-only mode, blocks that *would* be claimed).
	 */
	if (claim_txg == 0)
		return;

	zilog = zil_alloc(dp->dp_meta_objset, zh);

	(void) zil_parse(zilog, dsl_scan_zil_block, dsl_scan_zil_record, &zsa,
	    claim_txg, B_FALSE);

	zil_free(zilog);
}