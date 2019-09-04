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
struct wl_registry {int dummy; } ;
struct swaynag_pointer {int cursor_surface; } ;
struct swaynag {int scale; scalar_t__ querying_outputs; int surface; int layer_surface; TYPE_2__* type; TYPE_1__* output; scalar_t__ layer_shell; scalar_t__ compositor; struct swaynag_pointer pointer; int /*<<< orphan*/  display; scalar_t__ shm; int /*<<< orphan*/  outputs; } ;
struct TYPE_4__ {int /*<<< orphan*/  anchors; scalar_t__ output; } ;
struct TYPE_3__ {int /*<<< orphan*/ * wl_output; } ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  ZWLR_LAYER_SHELL_V1_LAYER_TOP ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  layer_surface_listener ; 
 int /*<<< orphan*/  registry_listener ; 
 int /*<<< orphan*/  surface_listener ; 
 int /*<<< orphan*/  sway_abort (char*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  swaynag_destroy (struct swaynag*) ; 
 void* wl_compositor_create_surface (scalar_t__) ; 
 int /*<<< orphan*/  wl_display_connect (int /*<<< orphan*/ *) ; 
 struct wl_registry* wl_display_get_registry (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_display_roundtrip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_registry_add_listener (struct wl_registry*,int /*<<< orphan*/ *,struct swaynag*) ; 
 int /*<<< orphan*/  wl_registry_destroy (struct wl_registry*) ; 
 int /*<<< orphan*/  wl_surface_add_listener (int,int /*<<< orphan*/ *,struct swaynag*) ; 
 int zwlr_layer_shell_v1_get_layer_surface (scalar_t__,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  zwlr_layer_surface_v1_add_listener (int,int /*<<< orphan*/ *,struct swaynag*) ; 
 int /*<<< orphan*/  zwlr_layer_surface_v1_set_anchor (int,int /*<<< orphan*/ ) ; 

void swaynag_setup(struct swaynag *swaynag) {
	swaynag->display = wl_display_connect(NULL);
	if (!swaynag->display) {
		sway_abort("Unable to connect to the compositor. "
				"If your compositor is running, check or set the "
				"WAYLAND_DISPLAY environment variable.");
	}

	swaynag->scale = 1;
	wl_list_init(&swaynag->outputs);

	struct wl_registry *registry = wl_display_get_registry(swaynag->display);
	wl_registry_add_listener(registry, &registry_listener, swaynag);
	wl_display_roundtrip(swaynag->display);
	assert(swaynag->compositor && swaynag->layer_shell && swaynag->shm);

	while (swaynag->querying_outputs > 0) {
		wl_display_roundtrip(swaynag->display);
	}

	if (!swaynag->output && swaynag->type->output) {
		sway_log(SWAY_ERROR, "Output '%s' not found", swaynag->type->output);
		swaynag_destroy(swaynag);
		exit(EXIT_FAILURE);
	}

	struct swaynag_pointer *pointer = &swaynag->pointer;
	pointer->cursor_surface = wl_compositor_create_surface(swaynag->compositor);
	assert(pointer->cursor_surface);

	swaynag->surface = wl_compositor_create_surface(swaynag->compositor);
	assert(swaynag->surface);
	wl_surface_add_listener(swaynag->surface, &surface_listener, swaynag);

	swaynag->layer_surface = zwlr_layer_shell_v1_get_layer_surface(
			swaynag->layer_shell, swaynag->surface,
			swaynag->output ? swaynag->output->wl_output : NULL,
			ZWLR_LAYER_SHELL_V1_LAYER_TOP, "swaynag");
	assert(swaynag->layer_surface);
	zwlr_layer_surface_v1_add_listener(swaynag->layer_surface,
			&layer_surface_listener, swaynag);
	zwlr_layer_surface_v1_set_anchor(swaynag->layer_surface,
			swaynag->type->anchors);

	wl_registry_destroy(registry);
}