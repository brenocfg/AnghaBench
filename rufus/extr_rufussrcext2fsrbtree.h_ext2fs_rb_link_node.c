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
struct rb_node {uintptr_t rb_parent_color; int /*<<< orphan*/ * rb_right; int /*<<< orphan*/  rb_left; } ;

/* Variables and functions */

__attribute__((used)) static inline void ext2fs_rb_link_node(struct rb_node * node,
				     struct rb_node * parent,
				     struct rb_node ** rb_link)
{
	node->rb_parent_color = (uintptr_t)parent;
	node->rb_left = node->rb_right = NULL;

	*rb_link = node;
}