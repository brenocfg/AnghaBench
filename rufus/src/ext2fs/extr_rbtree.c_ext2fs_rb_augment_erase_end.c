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
struct rb_node {int dummy; } ;
typedef  int /*<<< orphan*/  rb_augment_f ;

/* Variables and functions */
 int /*<<< orphan*/  ext2fs_rb_augment_path (struct rb_node*,int /*<<< orphan*/ ,void*) ; 

void ext2fs_rb_augment_erase_end(struct rb_node *node, rb_augment_f func, void *data)
{
	if (node)
		ext2fs_rb_augment_path(node, func, data);
}