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
struct i3bar_block {scalar_t__ ref_count; struct i3bar_block* color; struct i3bar_block* instance; struct i3bar_block* name; struct i3bar_block* min_width_str; struct i3bar_block* align; struct i3bar_block* short_text; struct i3bar_block* full_text; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct i3bar_block*) ; 

void i3bar_block_unref(struct i3bar_block *block) {
	if (block == NULL) {
		return;
	}

	if (--block->ref_count == 0) {
		free(block->full_text);
		free(block->short_text);
		free(block->align);
		free(block->min_width_str);
		free(block->name);
		free(block->instance);
		free(block->color);
		free(block);
	}
}