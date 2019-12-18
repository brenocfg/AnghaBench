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
struct TYPE_8__ {int /*<<< orphan*/  vdev_spa; int /*<<< orphan*/  vdev_guid; } ;
typedef  TYPE_1__ vdev_t ;
struct TYPE_9__ {scalar_t__ aux_count; unsigned long long aux_pool; int /*<<< orphan*/  aux_guid; } ;
typedef  TYPE_2__ spa_aux_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int /*<<< orphan*/ ) ; 
 TYPE_2__* avl_find (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_remove (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  kmem_free (TYPE_2__*,int) ; 
 unsigned long long spa_guid (int /*<<< orphan*/ ) ; 

void
spa_aux_remove(vdev_t *vd, avl_tree_t *avl)
{
	spa_aux_t search;
	spa_aux_t *aux;
	avl_index_t where;

	search.aux_guid = vd->vdev_guid;
	aux = avl_find(avl, &search, &where);

	ASSERT(aux != NULL);

	if (--aux->aux_count == 0) {
		avl_remove(avl, aux);
		kmem_free(aux, sizeof (spa_aux_t));
	} else if (aux->aux_pool == spa_guid(vd->vdev_spa)) {
		aux->aux_pool = 0ULL;
	}
}