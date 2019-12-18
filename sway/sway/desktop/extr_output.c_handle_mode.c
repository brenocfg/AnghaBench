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
struct wl_listener {int dummy; } ;
struct sway_output {int /*<<< orphan*/  server; int /*<<< orphan*/  configured; int /*<<< orphan*/  enabled; TYPE_1__* wlr_output; } ;
struct output_config {scalar_t__ enabled; } ;
struct TYPE_2__ {int /*<<< orphan*/  name; int /*<<< orphan*/ * current_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  apply_output_config (struct output_config*,struct sway_output*) ; 
 int /*<<< orphan*/  arrange_layers (struct sway_output*) ; 
 int /*<<< orphan*/  arrange_output (struct sway_output*) ; 
 struct output_config* find_output_config (struct sway_output*) ; 
 int /*<<< orphan*/  mode ; 
 struct sway_output* output ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 
 int /*<<< orphan*/  update_output_manager_config (int /*<<< orphan*/ ) ; 
 struct sway_output* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_mode(struct wl_listener *listener, void *data) {
	struct sway_output *output = wl_container_of(listener, output, mode);
	if (!output->configured && !output->enabled) {
		struct output_config *oc = find_output_config(output);
		if (output->wlr_output->current_mode != NULL &&
				(!oc || oc->enabled)) {
			// We want to enable this output, but it didn't work last time,
			// possibly because we hadn't enough CRTCs. Try again now that the
			// output has a mode.
			sway_log(SWAY_DEBUG, "Output %s has gained a CRTC, "
				"trying to enable it", output->wlr_output->name);
			apply_output_config(oc, output);
		}
		return;
	}
	if (!output->enabled || !output->configured) {
		return;
	}
	arrange_layers(output);
	arrange_output(output);
	transaction_commit_dirty();

	update_output_manager_config(output->server);
}