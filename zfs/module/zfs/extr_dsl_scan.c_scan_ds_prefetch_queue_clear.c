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
struct TYPE_10__ {int /*<<< orphan*/  spa_scrub_lock; } ;
typedef  TYPE_2__ spa_t ;
struct TYPE_11__ {int /*<<< orphan*/  spic_spc; } ;
typedef  TYPE_3__ scan_prefetch_issue_ctx_t ;
struct TYPE_12__ {int /*<<< orphan*/  scn_prefetch_queue; TYPE_1__* scn_dp; } ;
typedef  TYPE_4__ dsl_scan_t ;
struct TYPE_9__ {TYPE_2__* dp_spa; } ;

/* Variables and functions */
 TYPE_3__* avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  kmem_free (TYPE_3__*,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scan_prefetch_ctx_rele (int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void
scan_ds_prefetch_queue_clear(dsl_scan_t *scn)
{
	spa_t *spa = scn->scn_dp->dp_spa;
	void *cookie = NULL;
	scan_prefetch_issue_ctx_t *spic = NULL;

	mutex_enter(&spa->spa_scrub_lock);
	while ((spic = avl_destroy_nodes(&scn->scn_prefetch_queue,
	    &cookie)) != NULL) {
		scan_prefetch_ctx_rele(spic->spic_spc, scn);
		kmem_free(spic, sizeof (scan_prefetch_issue_ctx_t));
	}
	mutex_exit(&spa->spa_scrub_lock);
}