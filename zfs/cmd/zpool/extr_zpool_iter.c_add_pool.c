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
struct TYPE_8__ {int /*<<< orphan*/  zn_avlnode; int /*<<< orphan*/ * zn_handle; } ;
typedef  TYPE_1__ zpool_node_t ;
struct TYPE_9__ {int /*<<< orphan*/  zl_avl; scalar_t__ zl_proplist; int /*<<< orphan*/  zl_pool; } ;
typedef  TYPE_2__ zpool_list_t ;
typedef  int /*<<< orphan*/  zpool_handle_t ;
typedef  int /*<<< orphan*/  uu_avl_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 TYPE_1__* safe_malloc (int) ; 
 int /*<<< orphan*/ * uu_avl_find (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uu_avl_insert (int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uu_avl_node_init (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zpool_close (int /*<<< orphan*/ *) ; 
 scalar_t__ zpool_expand_proplist (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
add_pool(zpool_handle_t *zhp, void *data)
{
	zpool_list_t *zlp = data;
	zpool_node_t *node = safe_malloc(sizeof (zpool_node_t));
	uu_avl_index_t idx;

	node->zn_handle = zhp;
	uu_avl_node_init(node, &node->zn_avlnode, zlp->zl_pool);
	if (uu_avl_find(zlp->zl_avl, node, NULL, &idx) == NULL) {
		if (zlp->zl_proplist &&
		    zpool_expand_proplist(zhp, zlp->zl_proplist) != 0) {
			zpool_close(zhp);
			free(node);
			return (-1);
		}
		uu_avl_insert(zlp->zl_avl, node, idx);
	} else {
		zpool_close(zhp);
		free(node);
		return (-1);
	}

	return (0);
}