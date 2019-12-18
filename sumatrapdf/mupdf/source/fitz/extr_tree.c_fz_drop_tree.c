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
struct TYPE_5__ {void* value; struct TYPE_5__* key; struct TYPE_5__* right; struct TYPE_5__* left; } ;
typedef  TYPE_1__ fz_tree ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__ tree_sentinel ; 

void fz_drop_tree(fz_context *ctx, fz_tree *node, void (*dropfunc)(fz_context *ctx, void *value))
{
	if (node)
	{
		if (node->left != &tree_sentinel)
			fz_drop_tree(ctx, node->left, dropfunc);
		if (node->right != &tree_sentinel)
			fz_drop_tree(ctx, node->right, dropfunc);
		fz_free(ctx, node->key);
		if (dropfunc)
			dropfunc(ctx, node->value);
		fz_free(ctx, node);
	}
}