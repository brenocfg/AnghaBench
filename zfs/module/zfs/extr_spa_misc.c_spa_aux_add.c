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
struct TYPE_8__ {int /*<<< orphan*/  vdev_guid; } ;
typedef  TYPE_1__ vdev_t ;
struct TYPE_9__ {int aux_count; int /*<<< orphan*/  aux_guid; } ;
typedef  TYPE_2__ spa_aux_t ;
typedef  int /*<<< orphan*/  avl_tree_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  KM_SLEEP ; 
 TYPE_2__* avl_find (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  avl_insert (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_2__* kmem_zalloc (int,int /*<<< orphan*/ ) ; 

void
spa_aux_add(vdev_t *vd, avl_tree_t *avl)
{
	avl_index_t where;
	spa_aux_t search;
	spa_aux_t *aux;

	search.aux_guid = vd->vdev_guid;
	if ((aux = avl_find(avl, &search, &where)) != NULL) {
		aux->aux_count++;
	} else {
		aux = kmem_zalloc(sizeof (spa_aux_t), KM_SLEEP);
		aux->aux_guid = vd->vdev_guid;
		aux->aux_count = 1;
		avl_insert(avl, aux, where);
	}
}