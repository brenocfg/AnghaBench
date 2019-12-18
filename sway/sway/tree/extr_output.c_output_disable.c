#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  destroy; } ;
struct sway_output {int enabled; int configured; int /*<<< orphan*/ * current_mode; TYPE_2__ events; TYPE_1__* wlr_output; } ;
struct TYPE_6__ {int /*<<< orphan*/  outputs; } ;
struct TYPE_4__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  arrange_root () ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ ,int) ; 
 int list_find (int /*<<< orphan*/ ,struct sway_output*) ; 
 int /*<<< orphan*/  output_evacuate (struct sway_output*) ; 
 TYPE_3__* root ; 
 int /*<<< orphan*/  root_for_each_container (int /*<<< orphan*/ ,struct sway_output*) ; 
 int /*<<< orphan*/  sway_assert (int,char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  untrack_output ; 
 int /*<<< orphan*/  wl_signal_emit (int /*<<< orphan*/ *,struct sway_output*) ; 

void output_disable(struct sway_output *output) {
	if (!sway_assert(output->enabled, "Expected an enabled output")) {
		return;
	}
	sway_log(SWAY_DEBUG, "Disabling output '%s'", output->wlr_output->name);
	wl_signal_emit(&output->events.destroy, output);

	output_evacuate(output);

	root_for_each_container(untrack_output, output);

	int index = list_find(root->outputs, output);
	list_del(root->outputs, index);

	output->enabled = false;
	output->configured = false;
	output->current_mode = NULL;

	arrange_root();
}