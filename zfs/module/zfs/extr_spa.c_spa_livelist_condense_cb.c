#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zthr_t ;
typedef  void* uint64_t ;
struct TYPE_14__ {TYPE_1__* ds; int /*<<< orphan*/  syncing; TYPE_5__* next; TYPE_5__* first; } ;
struct TYPE_15__ {TYPE_2__ spa_to_condense; } ;
typedef  TYPE_3__ spa_t ;
struct TYPE_16__ {int /*<<< orphan*/  to_keep; void* next_size; void* first_size; TYPE_3__* spa; } ;
typedef  TYPE_4__ livelist_condense_arg_t ;
struct TYPE_17__ {int /*<<< orphan*/  dle_bpobj; } ;
typedef  TYPE_5__ dsl_deadlist_entry_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
struct TYPE_18__ {int /*<<< orphan*/  dp_mos_dir; } ;
struct TYPE_13__ {int /*<<< orphan*/  ds_dbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  B_TRUE ; 
 int EINTR ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int TXG_NOTHROTTLE ; 
 int TXG_NOWAIT ; 
 int /*<<< orphan*/  ZFS_SPACE_CHECK_NONE ; 
 int /*<<< orphan*/  bplist_clear (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bplist_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bplist_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  delay (int) ; 
 int /*<<< orphan*/  dmu_buf_rele (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int dmu_tx_assign (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dmu_tx_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * dmu_tx_create_dd (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dmu_tx_hold_space (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  dmu_tx_mark_netfree (int /*<<< orphan*/ *) ; 
 int dsl_process_sub_livelist (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  dsl_sync_task_nowait (TYPE_6__*,int /*<<< orphan*/ ,TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_free (TYPE_4__*,int) ; 
 TYPE_6__* spa_get_dsl (TYPE_3__*) ; 
 int /*<<< orphan*/  spa_livelist_condense_sync ; 
 scalar_t__ zfs_livelist_condense_sync_pause ; 
 int /*<<< orphan*/  zfs_livelist_condense_zthr_cancel ; 
 scalar_t__ zfs_livelist_condense_zthr_pause ; 
 scalar_t__ zthr_has_waiters (int /*<<< orphan*/ *) ; 
 scalar_t__ zthr_iscancelled (int /*<<< orphan*/ *) ; 

void
spa_livelist_condense_cb(void *arg, zthr_t *t)
{
	while (zfs_livelist_condense_zthr_pause &&
	    !(zthr_has_waiters(t) || zthr_iscancelled(t)))
		delay(1);

	spa_t *spa = arg;
	dsl_deadlist_entry_t *first = spa->spa_to_condense.first;
	dsl_deadlist_entry_t *next = spa->spa_to_condense.next;
	uint64_t first_size, next_size;

	livelist_condense_arg_t *lca =
	    kmem_alloc(sizeof (livelist_condense_arg_t), KM_SLEEP);
	bplist_create(&lca->to_keep);

	/*
	 * Process the livelists (matching FREEs and ALLOCs) in open context
	 * so we have minimal work in syncing context to condense.
	 *
	 * We save bpobj sizes (first_size and next_size) to use later in
	 * syncing context to determine if entries were added to these sublists
	 * while in open context. This is possible because the clone is still
	 * active and open for normal writes and we want to make sure the new,
	 * unprocessed blockpointers are inserted into the livelist normally.
	 *
	 * Note that dsl_process_sub_livelist() both stores the size number of
	 * blockpointers and iterates over them while the bpobj's lock held, so
	 * the sizes returned to us are consistent which what was actually
	 * processed.
	 */
	int err = dsl_process_sub_livelist(&first->dle_bpobj, &lca->to_keep, t,
	    &first_size);
	if (err == 0)
		err = dsl_process_sub_livelist(&next->dle_bpobj, &lca->to_keep,
		    t, &next_size);

	if (err == 0) {
		while (zfs_livelist_condense_sync_pause &&
		    !(zthr_has_waiters(t) || zthr_iscancelled(t)))
			delay(1);

		dmu_tx_t *tx = dmu_tx_create_dd(spa_get_dsl(spa)->dp_mos_dir);
		dmu_tx_mark_netfree(tx);
		dmu_tx_hold_space(tx, 1);
		err = dmu_tx_assign(tx, TXG_NOWAIT | TXG_NOTHROTTLE);
		if (err == 0) {
			/*
			 * Prevent the condense zthr restarting before
			 * the synctask completes.
			 */
			spa->spa_to_condense.syncing = B_TRUE;
			lca->spa = spa;
			lca->first_size = first_size;
			lca->next_size = next_size;
			dsl_sync_task_nowait(spa_get_dsl(spa),
			    spa_livelist_condense_sync, lca, 0,
			    ZFS_SPACE_CHECK_NONE, tx);
			dmu_tx_commit(tx);
			return;
		}
	}
	/*
	 * Condensing can not continue: either it was externally stopped or
	 * we were unable to assign to a tx because the pool has run out of
	 * space. In the second case, we'll just end up trying to condense
	 * again in a later txg.
	 */
	ASSERT(err != 0);
	bplist_clear(&lca->to_keep);
	bplist_destroy(&lca->to_keep);
	kmem_free(lca, sizeof (livelist_condense_arg_t));
	dmu_buf_rele(spa->spa_to_condense.ds->ds_dbuf, spa);
	spa->spa_to_condense.ds = NULL;
	if (err == EINTR)
		zfs_livelist_condense_zthr_cancel++;
}