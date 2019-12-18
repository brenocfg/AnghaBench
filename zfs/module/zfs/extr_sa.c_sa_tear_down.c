#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int sa_user_table_sz; int lot_attr_count; int /*<<< orphan*/  sa_lock; int /*<<< orphan*/  sa_layout_num_tree; int /*<<< orphan*/  sa_layout_hash_tree; struct TYPE_12__* lot_attrs; int /*<<< orphan*/  lot_idx_tab; struct TYPE_12__* sa_user_table; } ;
typedef  TYPE_1__ sa_os_t ;
typedef  TYPE_1__ sa_lot_t ;
struct TYPE_13__ {int /*<<< orphan*/  sa_refcount; } ;
typedef  TYPE_3__ sa_idx_tab_t ;
typedef  int /*<<< orphan*/  sa_attr_type_t ;
struct TYPE_14__ {TYPE_1__* os_sa; } ;
typedef  TYPE_4__ objset_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avl_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* avl_destroy_nodes (int /*<<< orphan*/ *,void**) ; 
 int /*<<< orphan*/  kmem_free (TYPE_1__*,int) ; 
 TYPE_3__* list_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sa_free_attr_table (TYPE_1__*) ; 
 int /*<<< orphan*/  sa_idx_tab_rele (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  zfs_refcount_count (int /*<<< orphan*/ *) ; 

void
sa_tear_down(objset_t *os)
{
	sa_os_t *sa = os->os_sa;
	sa_lot_t *layout;
	void *cookie;

	kmem_free(sa->sa_user_table, sa->sa_user_table_sz);

	/* Free up attr table */

	sa_free_attr_table(sa);

	cookie = NULL;
	while ((layout =
	    avl_destroy_nodes(&sa->sa_layout_hash_tree, &cookie))) {
		sa_idx_tab_t *tab;
		while ((tab = list_head(&layout->lot_idx_tab))) {
			ASSERT(zfs_refcount_count(&tab->sa_refcount));
			sa_idx_tab_rele(os, tab);
		}
	}

	cookie = NULL;
	while ((layout = avl_destroy_nodes(&sa->sa_layout_num_tree, &cookie))) {
		kmem_free(layout->lot_attrs,
		    sizeof (sa_attr_type_t) * layout->lot_attr_count);
		kmem_free(layout, sizeof (sa_lot_t));
	}

	avl_destroy(&sa->sa_layout_hash_tree);
	avl_destroy(&sa->sa_layout_num_tree);
	mutex_destroy(&sa->sa_lock);

	kmem_free(sa, sizeof (sa_os_t));
	os->os_sa = NULL;
}