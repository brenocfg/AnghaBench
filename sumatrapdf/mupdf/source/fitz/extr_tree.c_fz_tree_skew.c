#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ level; struct TYPE_4__* right; struct TYPE_4__* left; } ;
typedef  TYPE_1__ fz_tree ;

/* Variables and functions */

__attribute__((used)) static fz_tree *fz_tree_skew(fz_tree *node)
{
	if (node->level != 0)
	{
		if (node->left->level == node->level)
		{
			fz_tree *save = node;
			node = node->left;
			save->left = node->right;
			node->right = save;
		}
		node->right = fz_tree_skew(node->right);
	}
	return node;
}