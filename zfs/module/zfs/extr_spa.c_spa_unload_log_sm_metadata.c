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
struct TYPE_10__ {scalar_t__ sus_blocklimit; scalar_t__ sus_memused; scalar_t__ sus_nblocks; } ;
struct TYPE_11__ {TYPE_1__ spa_unflushed_stats; int /*<<< orphan*/  spa_log_summary; int /*<<< orphan*/  spa_sm_logs_by_txg; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_12__ {int /*<<< orphan*/  lse_mscount; int /*<<< orphan*/  sls_mscount; } ;
typedef  TYPE_3__ spa_log_sm_t ;
typedef  TYPE_3__ log_summary_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  VERIFY0 (int /*<<< orphan*/ ) ; 
 TYPE_3__* avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  kmem_free (TYPE_3__*,int) ; 
 TYPE_3__* list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void
spa_unload_log_sm_metadata(spa_t *spa)
{
	void *cookie = NULL;
	spa_log_sm_t *sls;
	while ((sls = avl_destroy_nodes(&spa->spa_sm_logs_by_txg,
	    &cookie)) != NULL) {
		VERIFY0(sls->sls_mscount);
		kmem_free(sls, sizeof (spa_log_sm_t));
	}

	for (log_summary_entry_t *e = list_head(&spa->spa_log_summary);
	    e != NULL; e = list_head(&spa->spa_log_summary)) {
		VERIFY0(e->lse_mscount);
		list_remove(&spa->spa_log_summary, e);
		kmem_free(e, sizeof (log_summary_entry_t));
	}

	spa->spa_unflushed_stats.sus_nblocks = 0;
	spa->spa_unflushed_stats.sus_memused = 0;
	spa->spa_unflushed_stats.sus_blocklimit = 0;
}