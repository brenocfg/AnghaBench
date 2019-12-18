#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  spa_errlist_lock; int /*<<< orphan*/  spa_errlist_scrub; int /*<<< orphan*/  spa_errlist_last; } ;
typedef  TYPE_1__ spa_t ;
typedef  int /*<<< orphan*/  spa_error_entry_t ;

/* Variables and functions */
 int /*<<< orphan*/ * avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  kmem_free (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  mutex_enter (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_exit (int /*<<< orphan*/ *) ; 

void
spa_errlog_drain(spa_t *spa)
{
	spa_error_entry_t *se;
	void *cookie;

	mutex_enter(&spa->spa_errlist_lock);

	cookie = NULL;
	while ((se = avl_destroy_nodes(&spa->spa_errlist_last,
	    &cookie)) != NULL)
		kmem_free(se, sizeof (spa_error_entry_t));
	cookie = NULL;
	while ((se = avl_destroy_nodes(&spa->spa_errlist_scrub,
	    &cookie)) != NULL)
		kmem_free(se, sizeof (spa_error_entry_t));

	mutex_exit(&spa->spa_errlist_lock);
}