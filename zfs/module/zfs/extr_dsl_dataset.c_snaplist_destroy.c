#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct promotenode {int /*<<< orphan*/  ds; } ;
struct TYPE_6__ {int /*<<< orphan*/  list_head; } ;
typedef  TYPE_1__ list_t ;

/* Variables and functions */
 int /*<<< orphan*/  dsl_dataset_rele (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  kmem_free (struct promotenode*,int) ; 
 int /*<<< orphan*/  list_destroy (TYPE_1__*) ; 
 int /*<<< orphan*/  list_link_active (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_remove (TYPE_1__*,struct promotenode*) ; 
 struct promotenode* list_tail (TYPE_1__*) ; 

__attribute__((used)) static void
snaplist_destroy(list_t *l, void *tag)
{
	struct promotenode *snap;

	if (l == NULL || !list_link_active(&l->list_head))
		return;

	while ((snap = list_tail(l)) != NULL) {
		list_remove(l, snap);
		dsl_dataset_rele(snap->ds, tag);
		kmem_free(snap, sizeof (*snap));
	}
	list_destroy(l);
}