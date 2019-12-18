#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_3__* zl_itxg; int /*<<< orphan*/  zl_spa; } ;
typedef  TYPE_2__ zilog_t ;
typedef  size_t uint64_t ;
struct TYPE_11__ {size_t itxg_txg; int /*<<< orphan*/  itxg_lock; TYPE_1__* itxg_itxs; } ;
typedef  TYPE_3__ itxg_t ;
struct TYPE_12__ {int /*<<< orphan*/  ia_list; } ;
typedef  TYPE_4__ itx_async_node_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
typedef  int /*<<< orphan*/  avl_index_t ;
struct TYPE_9__ {int /*<<< orphan*/  i_sync_list; int /*<<< orphan*/  i_async_tree; } ;

/* Variables and functions */
 size_t TXG_CONCURRENT_STATES ; 
 size_t TXG_MASK ; 
 scalar_t__ UINT64_MAX ; 
 size_t ZILTEST_TXG ; 
 TYPE_4__* avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 TYPE_4__* avl_find (int /*<<< orphan*/ *,size_t*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kmem_free (TYPE_4__*,int) ; 
 int /*<<< orphan*/  list_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_freeze_txg (int /*<<< orphan*/ ) ; 
 size_t spa_last_synced_txg (int /*<<< orphan*/ ) ; 

void
zil_async_to_sync(zilog_t *zilog, uint64_t foid)
{
	uint64_t otxg, txg;
	itx_async_node_t *ian;
	avl_tree_t *t;
	avl_index_t where;

	if (spa_freeze_txg(zilog->zl_spa) != UINT64_MAX) /* ziltest support */
		otxg = ZILTEST_TXG;
	else
		otxg = spa_last_synced_txg(zilog->zl_spa) + 1;

	/*
	 * This is inherently racy, since there is nothing to prevent
	 * the last synced txg from changing.
	 */
	for (txg = otxg; txg < (otxg + TXG_CONCURRENT_STATES); txg++) {
		itxg_t *itxg = &zilog->zl_itxg[txg & TXG_MASK];

		mutex_enter(&itxg->itxg_lock);
		if (itxg->itxg_txg != txg) {
			mutex_exit(&itxg->itxg_lock);
			continue;
		}

		/*
		 * If a foid is specified then find that node and append its
		 * list. Otherwise walk the tree appending all the lists
		 * to the sync list. We add to the end rather than the
		 * beginning to ensure the create has happened.
		 */
		t = &itxg->itxg_itxs->i_async_tree;
		if (foid != 0) {
			ian = avl_find(t, &foid, &where);
			if (ian != NULL) {
				list_move_tail(&itxg->itxg_itxs->i_sync_list,
				    &ian->ia_list);
			}
		} else {
			void *cookie = NULL;

			while ((ian = avl_destroy_nodes(t, &cookie)) != NULL) {
				list_move_tail(&itxg->itxg_itxs->i_sync_list,
				    &ian->ia_list);
				list_destroy(&ian->ia_list);
				kmem_free(ian, sizeof (itx_async_node_t));
			}
		}
		mutex_exit(&itxg->itxg_lock);
	}
}