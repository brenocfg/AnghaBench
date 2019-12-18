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
struct rb_root {int /*<<< orphan*/ * rb_node; } ;

/* Variables and functions */

__attribute__((used)) static inline int ext2fs_rb_empty_root(struct rb_root *root)
{
	return root->rb_node == NULL;
}