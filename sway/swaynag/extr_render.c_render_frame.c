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
typedef  int uint32_t ;
struct swaynag {int height; int width; int scale; int /*<<< orphan*/  display; int /*<<< orphan*/  surface; TYPE_1__* current_buffer; int /*<<< orphan*/  buffers; int /*<<< orphan*/  shm; int /*<<< orphan*/  layer_surface; int /*<<< orphan*/  run_display; } ;
typedef  int /*<<< orphan*/  cairo_t ;
typedef  int /*<<< orphan*/  cairo_surface_t ;
struct TYPE_2__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/ * cairo; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_CONTENT_COLOR_ALPHA ; 
 int /*<<< orphan*/  CAIRO_OPERATOR_CLEAR ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/ * cairo_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_paint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cairo_recording_surface_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_set_operator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_source_surface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 TYPE_1__* get_next_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int render_to_cairo (int /*<<< orphan*/ *,struct swaynag*) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl_display_roundtrip (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_attach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_commit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_damage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wl_surface_set_buffer_scale (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zwlr_layer_surface_v1_set_exclusive_zone (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zwlr_layer_surface_v1_set_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void render_frame(struct swaynag *swaynag) {
	if (!swaynag->run_display) {
		return;
	}

	cairo_surface_t *recorder = cairo_recording_surface_create(
			CAIRO_CONTENT_COLOR_ALPHA, NULL);
	cairo_t *cairo = cairo_create(recorder);
	cairo_save(cairo);
	cairo_set_operator(cairo, CAIRO_OPERATOR_CLEAR);
	cairo_paint(cairo);
	cairo_restore(cairo);
	uint32_t height = render_to_cairo(cairo, swaynag);
	if (height != swaynag->height) {
		zwlr_layer_surface_v1_set_size(swaynag->layer_surface, 0, height);
		zwlr_layer_surface_v1_set_exclusive_zone(swaynag->layer_surface,
				height);
		wl_surface_commit(swaynag->surface);
		wl_display_roundtrip(swaynag->display);
	} else {
		swaynag->current_buffer = get_next_buffer(swaynag->shm,
				swaynag->buffers,
				swaynag->width * swaynag->scale,
				swaynag->height * swaynag->scale);
		if (!swaynag->current_buffer) {
			sway_log(SWAY_DEBUG, "Failed to get buffer. Skipping frame.");
			goto cleanup;
		}

		cairo_t *shm = swaynag->current_buffer->cairo;
		cairo_save(shm);
		cairo_set_operator(shm, CAIRO_OPERATOR_CLEAR);
		cairo_paint(shm);
		cairo_restore(shm);
		cairo_set_source_surface(shm, recorder, 0.0, 0.0);
		cairo_paint(shm);

		wl_surface_set_buffer_scale(swaynag->surface, swaynag->scale);
		wl_surface_attach(swaynag->surface,
				swaynag->current_buffer->buffer, 0, 0);
		wl_surface_damage(swaynag->surface, 0, 0,
				swaynag->width, swaynag->height);
		wl_surface_commit(swaynag->surface);
		wl_display_roundtrip(swaynag->display);
	}

cleanup:
	cairo_surface_destroy(recorder);
	cairo_destroy(cairo);
}