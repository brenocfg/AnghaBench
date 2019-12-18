#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  link; } ;
struct sway_root {int /*<<< orphan*/  output_layout; int /*<<< orphan*/  outputs; int /*<<< orphan*/  scratchpad; TYPE_1__ output_layout_change; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sway_root*) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wlr_output_layout_destroy (int /*<<< orphan*/ ) ; 

void root_destroy(struct sway_root *root) {
	wl_list_remove(&root->output_layout_change.link);
	list_free(root->scratchpad);
	list_free(root->outputs);
	wlr_output_layout_destroy(root->output_layout);
	free(root);
}