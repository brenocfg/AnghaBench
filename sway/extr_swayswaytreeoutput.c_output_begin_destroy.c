#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int destroying; } ;
struct sway_output {TYPE_1__* wlr_output; int /*<<< orphan*/  link; TYPE_2__ node; int /*<<< orphan*/  enabled; } ;
struct TYPE_3__ {int /*<<< orphan*/ * data; int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  node_set_dirty (TYPE_2__*) ; 
 int /*<<< orphan*/  sway_assert (int,char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 

void output_begin_destroy(struct sway_output *output) {
	if (!sway_assert(!output->enabled, "Expected a disabled output")) {
		return;
	}
	sway_log(SWAY_DEBUG, "Destroying output '%s'", output->wlr_output->name);

	output->node.destroying = true;
	node_set_dirty(&output->node);

	wl_list_remove(&output->link);
	output->wlr_output->data = NULL;
	output->wlr_output = NULL;
}