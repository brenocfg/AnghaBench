#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ dl_object; int /*<<< orphan*/ * dl_os; int /*<<< orphan*/ * dl_phys; int /*<<< orphan*/ * dl_dbuf; int /*<<< orphan*/  dl_cache; scalar_t__ dl_havecache; int /*<<< orphan*/  dl_tree; scalar_t__ dl_havetree; int /*<<< orphan*/  dl_bpobj; scalar_t__ dl_oldfmt; int /*<<< orphan*/  dl_lock; } ;
typedef  TYPE_1__ dsl_deadlist_t ;
struct TYPE_10__ {int /*<<< orphan*/  dle_bpobj; } ;
typedef  TYPE_2__ dsl_deadlist_entry_t ;
typedef  TYPE_2__ dsl_deadlist_cache_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 scalar_t__ B_FALSE ; 
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 TYPE_2__* avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  bpobj_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dmu_buf_rele (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  dsl_deadlist_is_open (TYPE_1__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 

void
dsl_deadlist_close(dsl_deadlist_t *dl)
{
	ASSERT(dsl_deadlist_is_open(dl));
	mutex_destroy(&dl->dl_lock);

	if (dl->dl_oldfmt) {
		dl->dl_oldfmt = B_FALSE;
		bpobj_close(&dl->dl_bpobj);
		dl->dl_os = NULL;
		dl->dl_object = 0;
		return;
	}

	if (dl->dl_havetree) {
		dsl_deadlist_entry_t *dle;
		void *cookie = NULL;
		while ((dle = avl_destroy_nodes(&dl->dl_tree, &cookie))
		    != NULL) {
			bpobj_close(&dle->dle_bpobj);
			kmem_free(dle, sizeof (*dle));
		}
		avl_destroy(&dl->dl_tree);
	}
	if (dl->dl_havecache) {
		dsl_deadlist_cache_entry_t *dlce;
		void *cookie = NULL;
		while ((dlce = avl_destroy_nodes(&dl->dl_cache, &cookie))
		    != NULL) {
			kmem_free(dlce, sizeof (*dlce));
		}
		avl_destroy(&dl->dl_cache);
	}
	dmu_buf_rele(dl->dl_dbuf, dl);
	dl->dl_dbuf = NULL;
	dl->dl_phys = NULL;
	dl->dl_os = NULL;
	dl->dl_object = 0;
}