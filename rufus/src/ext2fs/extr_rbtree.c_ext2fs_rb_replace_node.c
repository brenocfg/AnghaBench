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
struct rb_node {struct rb_node* rb_right; struct rb_node* rb_left; } ;

/* Variables and functions */
 struct rb_node* ext2fs_rb_parent (struct rb_node*) ; 
 int /*<<< orphan*/  ext2fs_rb_set_parent (struct rb_node*,struct rb_node*) ; 

void ext2fs_rb_replace_node(struct rb_node *victim, struct rb_node *new,
			  struct rb_root *root)
{
	struct rb_node *parent = ext2fs_rb_parent(victim);

	/* Set the surrounding nodes to point to the replacement */
	if (parent) {
		if (victim == parent->rb_left)
			parent->rb_left = new;
		else
			parent->rb_right = new;
	} else {
		root->rb_node = new;
	}
	if (victim->rb_left)
		ext2fs_rb_set_parent(victim->rb_left, new);
	if (victim->rb_right)
		ext2fs_rb_set_parent(victim->rb_right, new);

	/* Copy the pointers/colour from the victim to the replacement */
	*new = *victim;
}