#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct rb_root {struct rb_node* rb_node; } ;
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; int /*<<< orphan*/  rb_parent_color; } ;

/* Variables and functions */
 int RB_BLACK ; 
 int /*<<< orphan*/  __rb_erase_color (struct rb_node*,struct rb_node*,struct rb_root*) ; 
 int ext2fs_rb_color (struct rb_node*) ; 
 struct rb_node* ext2fs_rb_parent (struct rb_node*) ; 
 int /*<<< orphan*/  ext2fs_rb_set_parent (struct rb_node*,struct rb_node*) ; 

void ext2fs_rb_erase(struct rb_node *node, struct rb_root *root)
{
	struct rb_node *child, *parent;
	int color;

	if (!node->rb_left)
		child = node->rb_right;
	else if (!node->rb_right)
		child = node->rb_left;
	else
	{
		struct rb_node *old = node, *left;

		node = node->rb_right;
		while ((left = node->rb_left) != NULL)
			node = left;

		if (ext2fs_rb_parent(old)) {
			if (ext2fs_rb_parent(old)->rb_left == old)
				ext2fs_rb_parent(old)->rb_left = node;
			else
				ext2fs_rb_parent(old)->rb_right = node;
		} else
			root->rb_node = node;

		child = node->rb_right;
		parent = ext2fs_rb_parent(node);
		color = ext2fs_rb_color(node);

		if (parent == old) {
			parent = node;
		} else {
			if (child)
				ext2fs_rb_set_parent(child, parent);
			parent->rb_left = child;

			node->rb_right = old->rb_right;
			ext2fs_rb_set_parent(old->rb_right, node);
		}

		node->rb_parent_color = old->rb_parent_color;
		node->rb_left = old->rb_left;
		ext2fs_rb_set_parent(old->rb_left, node);

		goto color;
	}

	parent = ext2fs_rb_parent(node);
	color = ext2fs_rb_color(node);

	if (child)
		ext2fs_rb_set_parent(child, parent);
	if (parent)
	{
		if (parent->rb_left == node)
			parent->rb_left = child;
		else
			parent->rb_right = child;
	}
	else
		root->rb_node = child;

 color:
	if (color == RB_BLACK)
		__rb_erase_color(child, parent, root);
}