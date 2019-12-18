#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_7__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zilog_t ;
struct TYPE_8__ {scalar_t__ zh_claim_txg; } ;
typedef  TYPE_1__ zil_header_t ;
typedef  scalar_t__ uint64_t ;
struct TYPE_9__ {int td_flags; int /*<<< orphan*/  td_spa; } ;
typedef  TYPE_2__ traverse_data_t ;
struct TYPE_10__ {int /*<<< orphan*/  dp_meta_objset; } ;

/* Variables and functions */
 int TRAVERSE_NO_DECRYPT ; 
 TYPE_7__* spa_get_dsl (int /*<<< orphan*/ ) ; 
 scalar_t__ spa_writeable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  traverse_zil_block ; 
 int /*<<< orphan*/  traverse_zil_record ; 
 int /*<<< orphan*/ * zil_alloc (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  zil_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zil_parse (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*,scalar_t__,int) ; 

__attribute__((used)) static void
traverse_zil(traverse_data_t *td, zil_header_t *zh)
{
	uint64_t claim_txg = zh->zh_claim_txg;

	/*
	 * We only want to visit blocks that have been claimed but not yet
	 * replayed; plus blocks that are already stable in read-only mode.
	 */
	if (claim_txg == 0 && spa_writeable(td->td_spa))
		return;

	zilog_t *zilog = zil_alloc(spa_get_dsl(td->td_spa)->dp_meta_objset, zh);
	(void) zil_parse(zilog, traverse_zil_block, traverse_zil_record, td,
	    claim_txg, !(td->td_flags & TRAVERSE_NO_DECRYPT));
	zil_free(zilog);
}