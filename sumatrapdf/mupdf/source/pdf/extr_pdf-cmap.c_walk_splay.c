#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int left; unsigned int right; unsigned int parent; } ;
typedef  TYPE_1__ cmap_splay ;

/* Variables and functions */
 unsigned int EMPTY ; 
#define  LEFT 130 
#define  RIGHT 129 
#define  TOP 128 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void walk_splay(cmap_splay *tree, unsigned int node, void (*fn)(cmap_splay *, void *), void *arg)
{
	int from = TOP;

	while (node != EMPTY)
	{
		switch (from)
		{
		case TOP:
			if (tree[node].left != EMPTY)
			{
				node = tree[node].left;
				from = TOP;
				break;
			}
			/* fallthrough */
		case LEFT:
			fn(&tree[node], arg);
			if (tree[node].right != EMPTY)
			{
				node = tree[node].right;
				from = TOP;
				break;
			}
			/* fallthrough */
		case RIGHT:
			{
				unsigned int parent = tree[node].parent;
				if (parent == EMPTY)
					return;
				if (tree[parent].left == node)
					from = LEFT;
				else
				{
					assert(tree[parent].right == node);
					from = RIGHT;
				}
				node = parent;
			}
		}
	}
}