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
struct TYPE_6__ {int /*<<< orphan*/  vdev_spa; int /*<<< orphan*/  vdev_guid; } ;
typedef  TYPE_1__ vdev_t ;
struct TYPE_7__ {unsigned long long aux_pool; int /*<<< orphan*/  aux_guid; } ;
typedef  TYPE_2__ spa_aux_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 TYPE_2__* avl_find (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 unsigned long long spa_guid (int /*<<< orphan*/ ) ; 

void
spa_aux_activate(vdev_t *vd, avl_tree_t *avl)
{
	spa_aux_t search, *found;
	avl_index_t where;

	search.aux_guid = vd->vdev_guid;
	found = avl_find(avl, &search, &where);
	ASSERT(found != NULL);
	ASSERT(found->aux_pool == 0ULL);

	found->aux_pool = spa_guid(vd->vdev_spa);
}