#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {struct TYPE_10__* right; struct TYPE_10__* left; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ fz_tree ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_1__* fz_tree_new_node (int /*<<< orphan*/ *,char const*,void*) ; 
 TYPE_1__* fz_tree_skew (TYPE_1__*) ; 
 TYPE_1__* fz_tree_split (TYPE_1__*) ; 
 int strcmp (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__ tree_sentinel ; 

fz_tree *fz_tree_insert(fz_context *ctx, fz_tree *node, const char *key, void *value)
{
	if (node && node != &tree_sentinel)
	{
		int c = strcmp(key, node->key);
		if (c < 0)
			node->left = fz_tree_insert(ctx, node->left, key, value);
		else
			node->right = fz_tree_insert(ctx, node->right, key, value);
		node = fz_tree_skew(node);
		node = fz_tree_split(node);
		return node;
	}
	else
	{
		return fz_tree_new_node(ctx, key, value);
	}
}