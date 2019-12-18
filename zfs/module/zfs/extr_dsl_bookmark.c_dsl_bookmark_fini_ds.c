#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  ds_bookmarks; scalar_t__ ds_is_snapshot; } ;
typedef  TYPE_1__ dsl_dataset_t ;
struct TYPE_7__ {int /*<<< orphan*/  dbn_lock; int /*<<< orphan*/  dbn_name; } ;
typedef  TYPE_2__ dsl_bookmark_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 TYPE_2__* avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spa_strfree (int /*<<< orphan*/ ) ; 

void
dsl_bookmark_fini_ds(dsl_dataset_t *ds)
{
	void *cookie = NULL;
	dsl_bookmark_node_t *dbn;

	if (ds->ds_is_snapshot)
		return;

	while ((dbn = avl_destroy_nodes(&ds->ds_bookmarks, &cookie)) != NULL) {
		spa_strfree(dbn->dbn_name);
		mutex_destroy(&dbn->dbn_lock);
		kmem_free(dbn, sizeof (*dbn));
	}
	avl_destroy(&ds->ds_bookmarks);
}