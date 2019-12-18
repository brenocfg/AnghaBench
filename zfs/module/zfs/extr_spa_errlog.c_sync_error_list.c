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
typedef  scalar_t__ uint64_t ;
struct TYPE_9__ {int /*<<< orphan*/  spa_meta_objset; } ;
typedef  TYPE_1__ spa_t ;
struct TYPE_10__ {char* se_name; int /*<<< orphan*/  se_bookmark; } ;
typedef  TYPE_2__ spa_error_entry_t ;
typedef  int /*<<< orphan*/  dmu_tx_t ;
typedef  int /*<<< orphan*/  buf ;
typedef  int /*<<< orphan*/  avl_tree_t ;

/* Variables and functions */
 TYPE_2__* AVL_NEXT (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  DMU_OT_ERROR_LOG ; 
 int /*<<< orphan*/  DMU_OT_NONE ; 
 TYPE_2__* avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 TYPE_2__* avl_first (int /*<<< orphan*/ *) ; 
 scalar_t__ avl_numnodes (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  bookmark_to_name (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 scalar_t__ strlen (char*) ; 
 scalar_t__ zap_create (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zap_update (int /*<<< orphan*/ ,scalar_t__,char*,int,scalar_t__,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
sync_error_list(spa_t *spa, avl_tree_t *t, uint64_t *obj, dmu_tx_t *tx)
{
	spa_error_entry_t *se;
	char buf[64];
	void *cookie;

	if (avl_numnodes(t) != 0) {
		/* create log if necessary */
		if (*obj == 0)
			*obj = zap_create(spa->spa_meta_objset,
			    DMU_OT_ERROR_LOG, DMU_OT_NONE,
			    0, tx);

		/* add errors to the current log */
		for (se = avl_first(t); se != NULL; se = AVL_NEXT(t, se)) {
			char *name = se->se_name ? se->se_name : "";

			bookmark_to_name(&se->se_bookmark, buf, sizeof (buf));

			(void) zap_update(spa->spa_meta_objset,
			    *obj, buf, 1, strlen(name) + 1, name, tx);
		}

		/* purge the error list */
		cookie = NULL;
		while ((se = avl_destroy_nodes(t, &cookie)) != NULL)
			kmem_free(se, sizeof (spa_error_entry_t));
	}
}