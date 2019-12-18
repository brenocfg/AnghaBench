#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {size_t avl_offset; TYPE_2__* avl_root; } ;
typedef  TYPE_1__ avl_tree_t ;
struct TYPE_6__ {struct TYPE_6__** avl_child; } ;
typedef  TYPE_2__ avl_node_t ;

/* Variables and functions */
 void* AVL_NODE2DATA (TYPE_2__*,size_t) ; 

void *
avl_first(avl_tree_t *tree)
{
	avl_node_t *node;
	avl_node_t *prev = NULL;
	size_t off = tree->avl_offset;

	for (node = tree->avl_root; node != NULL; node = node->avl_child[0])
		prev = node;

	if (prev != NULL)
		return (AVL_NODE2DATA(prev, off));
	return (NULL);
}