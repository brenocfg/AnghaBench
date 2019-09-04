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
struct rb_node {int rb_parent_color; } ;

/* Variables and functions */

__attribute__((used)) static inline void ext2fs_rb_set_parent(struct rb_node *rb, struct rb_node *p)
{
	rb->rb_parent_color = (rb->rb_parent_color & 3) | (uintptr_t)p;
}