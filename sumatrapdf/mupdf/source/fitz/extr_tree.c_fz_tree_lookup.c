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
struct TYPE_4__ {void* value; struct TYPE_4__* right; struct TYPE_4__* left; int /*<<< orphan*/  key; } ;
typedef  TYPE_1__ fz_tree ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int strcmp (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__ tree_sentinel ; 

void *fz_tree_lookup(fz_context *ctx, fz_tree *node, const char *key)
{
	if (node)
	{
		while (node != &tree_sentinel)
		{
			int c = strcmp(key, node->key);
			if (c == 0)
				return node->value;
			else if (c < 0)
				node = node->left;
			else
				node = node->right;
		}
	}
	return NULL;
}