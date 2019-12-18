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
typedef  int uint32_t ;
struct zxdg_output_v1 {int dummy; } ;
struct wl_registry {int dummy; } ;
struct swaynag_output {int wl_name; int scale; void* wl_output; int /*<<< orphan*/  link; struct swaynag* swaynag; } ;
struct swaynag {void* xdg_output_manager; void* layer_shell; int /*<<< orphan*/  outputs; int /*<<< orphan*/  querying_outputs; int /*<<< orphan*/  output; void* shm; void* seat; void* compositor; } ;
struct TYPE_8__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int ZXDG_OUTPUT_V1_NAME_SINCE_VERSION ; 
 struct swaynag_output* calloc (int,int) ; 
 int /*<<< orphan*/  output_listener ; 
 int /*<<< orphan*/  seat_listener ; 
 scalar_t__ strcmp (char const*,int /*<<< orphan*/ ) ; 
 TYPE_1__ wl_compositor_interface ; 
 int /*<<< orphan*/  wl_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_output_add_listener (void*,int /*<<< orphan*/ *,struct swaynag_output*) ; 
 TYPE_1__ wl_output_interface ; 
 void* wl_registry_bind (struct wl_registry*,int,TYPE_1__*,int) ; 
 int /*<<< orphan*/  wl_seat_add_listener (void*,int /*<<< orphan*/ *,struct swaynag*) ; 
 TYPE_1__ wl_seat_interface ; 
 TYPE_1__ wl_shm_interface ; 
 int /*<<< orphan*/  xdg_output_listener ; 
 TYPE_1__ zwlr_layer_shell_v1_interface ; 
 struct zxdg_output_v1* zxdg_output_manager_v1_get_xdg_output (void*,void*) ; 
 TYPE_1__ zxdg_output_manager_v1_interface ; 
 int /*<<< orphan*/  zxdg_output_v1_add_listener (struct zxdg_output_v1*,int /*<<< orphan*/ *,struct swaynag_output*) ; 

__attribute__((used)) static void handle_global(void *data, struct wl_registry *registry,
		uint32_t name, const char *interface, uint32_t version) {
	struct swaynag *swaynag = data;
	if (strcmp(interface, wl_compositor_interface.name) == 0) {
		swaynag->compositor = wl_registry_bind(registry, name,
				&wl_compositor_interface, 4);
	} else if (strcmp(interface, wl_seat_interface.name) == 0) {
		swaynag->seat = wl_registry_bind(registry, name, &wl_seat_interface, 1);
		wl_seat_add_listener(swaynag->seat, &seat_listener, swaynag);
	} else if (strcmp(interface, wl_shm_interface.name) == 0) {
		swaynag->shm = wl_registry_bind(registry, name, &wl_shm_interface, 1);
	} else if (strcmp(interface, wl_output_interface.name) == 0) {
		if (!swaynag->output && swaynag->xdg_output_manager) {
			swaynag->querying_outputs++;
			struct swaynag_output *output =
				calloc(1, sizeof(struct swaynag_output));
			output->wl_output = wl_registry_bind(registry, name,
					&wl_output_interface, 3);
			output->wl_name = name;
			output->scale = 1;
			output->swaynag = swaynag;
			wl_list_insert(&swaynag->outputs, &output->link);
			wl_output_add_listener(output->wl_output,
					&output_listener, output);

			struct zxdg_output_v1 *xdg_output;
			xdg_output = zxdg_output_manager_v1_get_xdg_output(
					swaynag->xdg_output_manager, output->wl_output);
			zxdg_output_v1_add_listener(xdg_output,
					&xdg_output_listener, output);
		}
	} else if (strcmp(interface, zwlr_layer_shell_v1_interface.name) == 0) {
		swaynag->layer_shell = wl_registry_bind(
				registry, name, &zwlr_layer_shell_v1_interface, 1);
	} else if (strcmp(interface, zxdg_output_manager_v1_interface.name) == 0
			&& version >= ZXDG_OUTPUT_V1_NAME_SINCE_VERSION) {
		swaynag->xdg_output_manager = wl_registry_bind(registry, name,
				&zxdg_output_manager_v1_interface,
				ZXDG_OUTPUT_V1_NAME_SINCE_VERSION);
	}
}