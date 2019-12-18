#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zbookmark_phys_t ;
struct TYPE_8__ {int /*<<< orphan*/  spa_errlist_lock; int /*<<< orphan*/  spa_errlist_last; int /*<<< orphan*/  spa_errlist_scrub; scalar_t__ spa_scrub_finished; scalar_t__ spa_scrub_active; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_9__ {int /*<<< orphan*/  se_bookmark; } ;
typedef  TYPE_2__ spa_error_entry_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 scalar_t__ SPA_LOAD_TRYIMPORT ; 
 int /*<<< orphan*/ * avl_find (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_insert (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 
 scalar_t__ spa_load_state (TYPE_1__*) ; 

void
spa_log_error(spa_t *spa, const zbookmark_phys_t *zb)
{
	spa_error_entry_t search;
	spa_error_entry_t *new;
	avl_tree_t *tree;
	avl_index_t where;

	/*
	 * If we are trying to import a pool, ignore any errors, as we won't be
	 * writing to the pool any time soon.
	 */
	if (spa_load_state(spa) == SPA_LOAD_TRYIMPORT)
		return;

	mutex_enter(&spa->spa_errlist_lock);

	/*
	 * If we have had a request to rotate the log, log it to the next list
	 * instead of the current one.
	 */
	if (spa->spa_scrub_active || spa->spa_scrub_finished)
		tree = &spa->spa_errlist_scrub;
	else
		tree = &spa->spa_errlist_last;

	search.se_bookmark = *zb;
	if (avl_find(tree, &search, &where) != NULL) {
		mutex_exit(&spa->spa_errlist_lock);
		return;
	}

	new = kmem_zalloc(sizeof (spa_error_entry_t), KM_SLEEP);
	new->se_bookmark = *zb;
	avl_insert(tree, new, where);

	mutex_exit(&spa->spa_errlist_lock);
}