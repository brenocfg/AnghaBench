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
struct wl_listener {int dummy; } ;
struct sway_output {int /*<<< orphan*/  server; int /*<<< orphan*/  configured; int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  arrange_layers (struct sway_output*) ; 
 int /*<<< orphan*/  arrange_output (struct sway_output*) ; 
 struct sway_output* output ; 
 int /*<<< orphan*/  output_for_each_container (struct sway_output*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scale ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 
 int /*<<< orphan*/  update_output_manager_config (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  update_textures ; 
 struct sway_output* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void handle_scale(struct wl_listener *listener, void *data) {
	struct sway_output *output = wl_container_of(listener, output, scale);
	if (!output->enabled || !output->configured) {
		return;
	}
	arrange_layers(output);
	output_for_each_container(output, update_textures, NULL);
	arrange_output(output);
	transaction_commit_dirty();

	update_output_manager_config(output->server);
}