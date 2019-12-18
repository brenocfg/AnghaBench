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
typedef  int /*<<< orphan*/  fs_perm_t ;
struct TYPE_9__ {int /*<<< orphan*/  fsps_deleg_perm_avl_pool; int /*<<< orphan*/  fsps_who_perm_avl_pool; int /*<<< orphan*/  fsps_named_set_avl_pool; int /*<<< orphan*/  fsps_list; } ;
typedef  TYPE_1__ fs_perm_set_t ;
struct TYPE_10__ {int /*<<< orphan*/  fspn_fsperm; } ;
typedef  TYPE_2__ fs_perm_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  fs_perm_fini (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uu_avl_pool_destroy (int /*<<< orphan*/ ) ; 
 TYPE_2__* uu_list_first (int /*<<< orphan*/ ) ; 
 TYPE_2__* uu_list_next (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  uu_list_remove (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static inline void
fs_perm_set_fini(fs_perm_set_t *fspset)
{
	fs_perm_node_t *node = uu_list_first(fspset->fsps_list);

	while (node != NULL) {
		fs_perm_node_t *next_node =
		    uu_list_next(fspset->fsps_list, node);
		fs_perm_t *fsperm = &node->fspn_fsperm;
		fs_perm_fini(fsperm);
		uu_list_remove(fspset->fsps_list, node);
		free(node);
		node = next_node;
	}

	uu_avl_pool_destroy(fspset->fsps_named_set_avl_pool);
	uu_avl_pool_destroy(fspset->fsps_who_perm_avl_pool);
	uu_avl_pool_destroy(fspset->fsps_deleg_perm_avl_pool);
}