#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {unsigned int parent; unsigned int left; unsigned int right; } ;
typedef  TYPE_1__ cmap_splay ;

/* Variables and functions */
 unsigned int EMPTY ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static void
move_to_root(cmap_splay *tree, unsigned int x)
{
	if (x == EMPTY)
		return;
	do
	{
		unsigned int z, zp;
		unsigned int y = tree[x].parent;
		if (y == EMPTY)
			break;
		z = tree[y].parent;
		if (z == EMPTY)
		{
			/* Case 3 */
			tree[x].parent = EMPTY;
			tree[y].parent = x;
			if (tree[y].left == x)
			{
				/* Case 3 */
				tree[y].left = tree[x].right;
				if (tree[y].left != EMPTY)
					tree[tree[y].left].parent = y;
				tree[x].right = y;
			}
			else
			{
				/* Case 3 - reflected */
				assert(tree[y].right == x);
				tree[y].right = tree[x].left;
				if (tree[y].right != EMPTY)
					tree[tree[y].right].parent = y;
				tree[x].left = y;
			}
			break;
		}

		zp = tree[z].parent;
		tree[x].parent = zp;
		if (zp != EMPTY) {
			if (tree[zp].left == z)
				tree[zp].left = x;
			else
			{
				assert(tree[zp].right == z);
				tree[zp].right = x;
			}
		}
		tree[y].parent = x;
		if (tree[y].left == x)
		{
			tree[y].left = tree[x].right;
			if (tree[y].left != EMPTY)
				tree[tree[y].left].parent = y;
			tree[x].right = y;
			if (tree[z].left == y)
			{
				/* Case 1 */
				tree[z].parent = y;
				tree[z].left = tree[y].right;
				if (tree[z].left != EMPTY)
					tree[tree[z].left].parent = z;
				tree[y].right = z;
			}
			else
			{
				/* Case 2 - reflected */
				assert(tree[z].right == y);
				tree[z].parent = x;
				tree[z].right = tree[x].left;
				if (tree[z].right != EMPTY)
					tree[tree[z].right].parent = z;
				tree[x].left = z;
			}
		}
		else
		{
			assert(tree[y].right == x);
			tree[y].right = tree[x].left;
			if (tree[y].right != EMPTY)
				tree[tree[y].right].parent = y;
			tree[x].left = y;
			if (tree[z].left == y)
			{
				/* Case 2 */
				tree[z].parent = x;
				tree[z].left = tree[x].right;
				if (tree[z].left != EMPTY)
					tree[tree[z].left].parent = z;
				tree[x].right = z;
			}
			else
			{
				/* Case 1 - reflected */
				assert(tree[z].right == y);
				tree[z].parent = y;
				tree[z].right = tree[y].left;
				if (tree[z].right != EMPTY)
					tree[tree[z].right].parent = z;
				tree[y].left = z;
			}
		}
	} while (1);
}