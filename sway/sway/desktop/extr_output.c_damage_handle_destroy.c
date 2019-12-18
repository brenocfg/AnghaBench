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
struct sway_output {int /*<<< orphan*/  enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  damage_destroy ; 
 struct sway_output* output ; 
 int /*<<< orphan*/  output_disable (struct sway_output*) ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 
 struct sway_output* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void damage_handle_destroy(struct wl_listener *listener, void *data) {
	struct sway_output *output =
		wl_container_of(listener, output, damage_destroy);
	if (!output->enabled) {
		return;
	}
	output_disable(output);
	transaction_commit_dirty();
}