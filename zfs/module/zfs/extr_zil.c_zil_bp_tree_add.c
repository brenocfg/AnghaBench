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
struct TYPE_6__ {int /*<<< orphan*/  zl_bp_tree; } ;
typedef  TYPE_1__ zilog_t ;
struct TYPE_7__ {int /*<<< orphan*/  zn_dva; } ;
typedef  TYPE_2__ zil_bp_node_t ;
typedef  int /*<<< orphan*/  dva_t ;
typedef  int /*<<< orphan*/  blkptr_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int /*<<< orphan*/ * BP_IDENTITY (int /*<<< orphan*/  const*) ; 
 scalar_t__ BP_IS_EMBEDDED (int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  EEXIST ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int SET_ERROR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * avl_find (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_insert (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* kmem_alloc (int,int /*<<< orphan*/ ) ; 

int
zil_bp_tree_add(zilog_t *zilog, const blkptr_t *bp)
{
	avl_tree_t *t = &zilog->zl_bp_tree;
	const dva_t *dva;
	zil_bp_node_t *zn;
	avl_index_t where;

	if (BP_IS_EMBEDDED(bp))
		return (0);

	dva = BP_IDENTITY(bp);

	if (avl_find(t, dva, &where) != NULL)
		return (SET_ERROR(EEXIST));

	zn = kmem_alloc(sizeof (zil_bp_node_t), KM_SLEEP);
	zn->zn_dva = *dva;
	avl_insert(t, zn, where);

	return (0);
}