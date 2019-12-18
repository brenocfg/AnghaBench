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
typedef  scalar_t__ uint32_t ;
struct wl_registry {int dummy; } ;
struct swaynag {int run_display; TYPE_1__* output; } ;
struct TYPE_2__ {scalar_t__ wl_name; } ;

/* Variables and functions */

__attribute__((used)) static void handle_global_remove(void *data, struct wl_registry *registry,
		uint32_t name) {
	struct swaynag *swaynag = data;
	if (swaynag->output->wl_name == name) {
		swaynag->run_display = false;
	}
}