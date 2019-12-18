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
struct TYPE_6__ {size_t avl_offset; int (* avl_compar ) (void const*,void*) ;TYPE_2__* avl_root; } ;
typedef  TYPE_1__ avl_tree_t ;
struct TYPE_7__ {struct TYPE_7__** avl_child; } ;
typedef  TYPE_2__ avl_node_t ;
typedef  int /*<<< orphan*/  avl_index_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  AVL_MKINDEX (TYPE_2__*,int) ; 
 void* AVL_NODE2DATA (TYPE_2__*,size_t) ; 
 int* avl_balance2child ; 
 int stub1 (void const*,void*) ; 

void *
avl_find(avl_tree_t *tree, const void *value, avl_index_t *where)
{
	avl_node_t *node;
	avl_node_t *prev = NULL;
	int child = 0;
	int diff;
	size_t off = tree->avl_offset;

	for (node = tree->avl_root; node != NULL;
	    node = node->avl_child[child]) {

		prev = node;

		diff = tree->avl_compar(value, AVL_NODE2DATA(node, off));
		ASSERT(-1 <= diff && diff <= 1);
		if (diff == 0) {
#ifdef DEBUG
			if (where != NULL)
				*where = 0;
#endif
			return (AVL_NODE2DATA(node, off));
		}
		child = avl_balance2child[1 + diff];

	}

	if (where != NULL)
		*where = AVL_MKINDEX(prev, child);

	return (NULL);
}