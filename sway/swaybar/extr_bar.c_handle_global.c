#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  void* uint32_t ;
struct wl_registry {int dummy; } ;
struct swaybar_seat {int /*<<< orphan*/  link; void* wl_seat; void* wl_name; struct swaybar* bar; } ;
struct swaybar_output {int scale; int /*<<< orphan*/  link; int /*<<< orphan*/  hotspots; int /*<<< orphan*/  workspaces; void* wl_name; void* output; struct swaybar* bar; } ;
struct swaybar {int /*<<< orphan*/ * xdg_output_manager; void* layer_shell; void* shm; int /*<<< orphan*/  seats; void* compositor; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_xdg_output (struct swaybar_output*) ; 
 void* calloc (int,int) ; 
 int /*<<< orphan*/  output_listener ; 
 int /*<<< orphan*/  seat_listener ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_abort (char*) ; 
 TYPE_1__ wl_compositor_interface ; 
 int /*<<< orphan*/  wl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_output_add_listener (void*,int /*<<< orphan*/ *,struct swaybar_output*) ; 
 TYPE_1__ wl_output_interface ; 
 void* wl_registry_bind (struct wl_registry*,void*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  wl_seat_add_listener (void*,int /*<<< orphan*/ *,struct swaybar_seat*) ; 
 TYPE_1__ wl_seat_interface ; 
 TYPE_1__ wl_shm_interface ; 
 TYPE_1__ zwlr_layer_shell_v1_interface ; 
 TYPE_1__ zxdg_output_manager_v1_interface ; 

__attribute__((used)) static void handle_global(void *data, struct wl_registry *registry,
		uint32_t name, const char *interface, uint32_t version) {
	struct swaybar *bar = data;
	if (strcmp(interface, wl_compositor_interface.name) == 0) {
		bar->compositor = wl_registry_bind(registry, name,
				&wl_compositor_interface, 4);
	} else if (strcmp(interface, wl_seat_interface.name) == 0) {
		struct swaybar_seat *seat = calloc(1, sizeof(struct swaybar_seat));
		if (!seat) {
			sway_abort("Failed to allocate swaybar_seat");
			return;
		}
		seat->bar = bar;
		seat->wl_name = name;
		seat->wl_seat = wl_registry_bind(registry, name, &wl_seat_interface, 3);
		wl_seat_add_listener(seat->wl_seat, &seat_listener, seat);
		wl_list_insert(&bar->seats, &seat->link);
	} else if (strcmp(interface, wl_shm_interface.name) == 0) {
		bar->shm = wl_registry_bind(registry, name,
				&wl_shm_interface, 1);
	} else if (strcmp(interface, wl_output_interface.name) == 0) {
		struct swaybar_output *output =
			calloc(1, sizeof(struct swaybar_output));
		output->bar = bar;
		output->output = wl_registry_bind(registry, name,
				&wl_output_interface, 3);
		wl_output_add_listener(output->output, &output_listener, output);
		output->scale = 1;
		output->wl_name = name;
		wl_list_init(&output->workspaces);
		wl_list_init(&output->hotspots);
		wl_list_init(&output->link);
		if (bar->xdg_output_manager != NULL) {
			add_xdg_output(output);
		}
	} else if (strcmp(interface, zwlr_layer_shell_v1_interface.name) == 0) {
		bar->layer_shell = wl_registry_bind(
				registry, name, &zwlr_layer_shell_v1_interface, 1);
	} else if (strcmp(interface, zxdg_output_manager_v1_interface.name) == 0) {
		bar->xdg_output_manager = wl_registry_bind(registry, name,
			&zxdg_output_manager_v1_interface, 2);
	}
}