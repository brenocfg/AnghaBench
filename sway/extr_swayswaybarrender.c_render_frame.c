#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct wl_callback {int dummy; } ;
struct swaybar_output {int height; scalar_t__ width; int scale; int frame_scheduled; int /*<<< orphan*/ * surface; TYPE_4__* current_buffer; int /*<<< orphan*/  buffers; TYPE_3__* bar; int /*<<< orphan*/  layer_surface; int /*<<< orphan*/  subpixel; int /*<<< orphan*/  hotspots; } ;
typedef  int /*<<< orphan*/  cairo_t ;
typedef  int /*<<< orphan*/  cairo_surface_t ;
typedef  int /*<<< orphan*/  cairo_font_options_t ;
struct TYPE_8__ {int /*<<< orphan*/  buffer; int /*<<< orphan*/ * cairo; } ;
struct TYPE_7__ {int /*<<< orphan*/  shm; TYPE_2__* config; } ;
struct TYPE_5__ {int /*<<< orphan*/  left; int /*<<< orphan*/  bottom; int /*<<< orphan*/  right; int /*<<< orphan*/  top; } ;
struct TYPE_6__ {int height; int /*<<< orphan*/  mode; TYPE_1__ gaps; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_ANTIALIAS_BEST ; 
 int /*<<< orphan*/  CAIRO_ANTIALIAS_SUBPIXEL ; 
 int /*<<< orphan*/  CAIRO_CONTENT_COLOR_ALPHA ; 
 int /*<<< orphan*/  CAIRO_HINT_STYLE_FULL ; 
 int /*<<< orphan*/  CAIRO_OPERATOR_CLEAR ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * cairo_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cairo_font_options_create () ; 
 int /*<<< orphan*/  cairo_font_options_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_font_options_set_antialias (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_font_options_set_hint_style (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_font_options_set_subpixel_order (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_paint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cairo_recording_surface_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_set_antialias (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_font_options (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_set_operator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_source_surface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  cairo_surface_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free_hotspots (int /*<<< orphan*/ *) ; 
 TYPE_4__* get_next_buffer (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  output_frame_listener ; 
 int render_to_cairo (int /*<<< orphan*/ *,struct swaybar_output*) ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  to_cairo_subpixel_order (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_callback_add_listener (struct wl_callback*,int /*<<< orphan*/ *,struct swaybar_output*) ; 
 int /*<<< orphan*/  wl_surface_attach (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_surface_commit (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_surface_damage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 struct wl_callback* wl_surface_frame (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_surface_set_buffer_scale (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zwlr_layer_surface_v1_set_exclusive_zone (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zwlr_layer_surface_v1_set_margin (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zwlr_layer_surface_v1_set_size (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

void render_frame(struct swaybar_output *output) {
	assert(output->surface != NULL);
	if (!output->layer_surface) {
		return;
	}

	free_hotspots(&output->hotspots);

	cairo_surface_t *recorder = cairo_recording_surface_create(
			CAIRO_CONTENT_COLOR_ALPHA, NULL);
	cairo_t *cairo = cairo_create(recorder);
	cairo_set_antialias(cairo, CAIRO_ANTIALIAS_BEST);
	cairo_font_options_t *fo = cairo_font_options_create();
	cairo_font_options_set_hint_style(fo, CAIRO_HINT_STYLE_FULL);
	cairo_font_options_set_antialias(fo, CAIRO_ANTIALIAS_SUBPIXEL);
	cairo_font_options_set_subpixel_order(fo, to_cairo_subpixel_order(output->subpixel));
	cairo_set_font_options(cairo, fo);
	cairo_font_options_destroy(fo);
	cairo_save(cairo);
	cairo_set_operator(cairo, CAIRO_OPERATOR_CLEAR);
	cairo_paint(cairo);
	cairo_restore(cairo);
	uint32_t height = render_to_cairo(cairo, output);
	int config_height = output->bar->config->height;
	if (config_height > 0) {
		height = config_height;
	}
	if (height != output->height || output->width == 0) {
		// Reconfigure surface
		zwlr_layer_surface_v1_set_size(output->layer_surface, 0, height);
		zwlr_layer_surface_v1_set_margin(output->layer_surface,
				output->bar->config->gaps.top,
				output->bar->config->gaps.right,
				output->bar->config->gaps.bottom,
				output->bar->config->gaps.left);
		if (strcmp(output->bar->config->mode, "dock") == 0) {
			zwlr_layer_surface_v1_set_exclusive_zone(output->layer_surface, height);
		}
		// TODO: this could infinite loop if the compositor assigns us a
		// different height than what we asked for
		wl_surface_commit(output->surface);
	} else if (height > 0) {
		// Replay recording into shm and send it off
		output->current_buffer = get_next_buffer(output->bar->shm,
				output->buffers,
				output->width * output->scale,
				output->height * output->scale);
		if (!output->current_buffer) {
			cairo_surface_destroy(recorder);
			cairo_destroy(cairo);
			return;
		}
		cairo_t *shm = output->current_buffer->cairo;

		cairo_save(shm);
		cairo_set_operator(shm, CAIRO_OPERATOR_CLEAR);
		cairo_paint(shm);
		cairo_restore(shm);

		cairo_set_source_surface(shm, recorder, 0.0, 0.0);
		cairo_paint(shm);

		wl_surface_set_buffer_scale(output->surface, output->scale);
		wl_surface_attach(output->surface,
				output->current_buffer->buffer, 0, 0);
		wl_surface_damage(output->surface, 0, 0,
				output->width, output->height);

		struct wl_callback *frame_callback = wl_surface_frame(output->surface);
		wl_callback_add_listener(frame_callback, &output_frame_listener, output);
		output->frame_scheduled = true;

		wl_surface_commit(output->surface);
	}
	cairo_surface_destroy(recorder);
	cairo_destroy(cairo);
}