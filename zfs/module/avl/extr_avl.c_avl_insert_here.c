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
struct TYPE_8__ {int (* avl_compar ) (void*,void*) ;int /*<<< orphan*/  avl_offset; } ;
typedef  TYPE_1__ avl_tree_t ;
struct TYPE_9__ {struct TYPE_9__** avl_child; } ;
typedef  TYPE_2__ avl_node_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int AVL_AFTER ; 
 int AVL_BEFORE ; 
 TYPE_2__* AVL_DATA2NODE (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AVL_MKINDEX (TYPE_2__*,int) ; 
 void* AVL_NODE2DATA (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  avl_insert (TYPE_1__*,void*,int /*<<< orphan*/ ) ; 
 int stub1 (void*,void*) ; 
 int stub2 (void*,void*) ; 
 int stub3 (void*,void*) ; 

void
avl_insert_here(
	avl_tree_t *tree,
	void *new_data,
	void *here,
	int direction)
{
	avl_node_t *node;
	int child = direction;	/* rely on AVL_BEFORE == 0, AVL_AFTER == 1 */
#ifdef DEBUG
	int diff;
#endif

	ASSERT(tree != NULL);
	ASSERT(new_data != NULL);
	ASSERT(here != NULL);
	ASSERT(direction == AVL_BEFORE || direction == AVL_AFTER);

	/*
	 * If corresponding child of node is not NULL, go to the neighboring
	 * node and reverse the insertion direction.
	 */
	node = AVL_DATA2NODE(here, tree->avl_offset);

#ifdef DEBUG
	diff = tree->avl_compar(new_data, here);
	ASSERT(-1 <= diff && diff <= 1);
	ASSERT(diff != 0);
	ASSERT(diff > 0 ? child == 1 : child == 0);
#endif

	if (node->avl_child[child] != NULL) {
		node = node->avl_child[child];
		child = 1 - child;
		while (node->avl_child[child] != NULL) {
#ifdef DEBUG
			diff = tree->avl_compar(new_data,
			    AVL_NODE2DATA(node, tree->avl_offset));
			ASSERT(-1 <= diff && diff <= 1);
			ASSERT(diff != 0);
			ASSERT(diff > 0 ? child == 1 : child == 0);
#endif
			node = node->avl_child[child];
		}
#ifdef DEBUG
		diff = tree->avl_compar(new_data,
		    AVL_NODE2DATA(node, tree->avl_offset));
		ASSERT(-1 <= diff && diff <= 1);
		ASSERT(diff != 0);
		ASSERT(diff > 0 ? child == 1 : child == 0);
#endif
	}
	ASSERT(node->avl_child[child] == NULL);

	avl_insert(tree, new_data, AVL_MKINDEX(node, child));
}