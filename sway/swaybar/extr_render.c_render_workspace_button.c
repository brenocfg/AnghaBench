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
typedef  scalar_t__ uint32_t ;
struct swaybar_workspace {int /*<<< orphan*/  name; int /*<<< orphan*/  label; scalar_t__ visible; scalar_t__ focused; scalar_t__ urgent; } ;
struct swaybar_output {scalar_t__ height; scalar_t__ scale; int /*<<< orphan*/  hotspots; TYPE_2__* bar; } ;
struct swaybar_hotspot {double x; int /*<<< orphan*/  link; int /*<<< orphan*/  data; int /*<<< orphan*/  destroy; int /*<<< orphan*/  callback; scalar_t__ height; scalar_t__ width; scalar_t__ y; } ;
struct box_colors {int /*<<< orphan*/  text; int /*<<< orphan*/  border; int /*<<< orphan*/  background; } ;
struct TYPE_3__ {struct box_colors inactive_workspace; struct box_colors active_workspace; struct box_colors focused_workspace; struct box_colors urgent_workspace; } ;
struct swaybar_config {int /*<<< orphan*/  pango_markup; int /*<<< orphan*/  font; int /*<<< orphan*/  height; TYPE_1__ colors; } ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_4__ {struct swaybar_config* config; } ;

/* Variables and functions */
 int BORDER_WIDTH ; 
 int WS_HORIZONTAL_PADDING ; 
 int WS_VERTICAL_PADDING ; 
 int /*<<< orphan*/  cairo_fill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_move_to (int /*<<< orphan*/ *,double,int) ; 
 int /*<<< orphan*/  cairo_rectangle (int /*<<< orphan*/ *,double,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  cairo_set_source_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct swaybar_hotspot* calloc (int,int) ; 
 scalar_t__ floor (double) ; 
 int /*<<< orphan*/  free ; 
 int /*<<< orphan*/  get_text_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  workspace_hotspot_callback ; 

__attribute__((used)) static uint32_t render_workspace_button(cairo_t *cairo,
		struct swaybar_output *output,
		struct swaybar_workspace *ws, double *x) {
	struct swaybar_config *config = output->bar->config;
	struct box_colors box_colors;
	if (ws->urgent) {
		box_colors = config->colors.urgent_workspace;
	} else if (ws->focused) {
		box_colors = config->colors.focused_workspace;
	} else if (ws->visible) {
		box_colors = config->colors.active_workspace;
	} else {
		box_colors = config->colors.inactive_workspace;
	}

	uint32_t height = output->height * output->scale;

	int text_width, text_height;
	get_text_size(cairo, config->font, &text_width, &text_height, NULL,
			output->scale, config->pango_markup, "%s", ws->label);

	int ws_vertical_padding = WS_VERTICAL_PADDING * output->scale;
	int ws_horizontal_padding = WS_HORIZONTAL_PADDING * output->scale;
	int border_width = BORDER_WIDTH * output->scale;

	uint32_t ideal_height = ws_vertical_padding * 2 + text_height
		+ border_width * 2;
	uint32_t ideal_surface_height = ideal_height / output->scale;
	if (!output->bar->config->height &&
			output->height < ideal_surface_height) {
		return ideal_surface_height;
	}

	uint32_t width = ws_horizontal_padding * 2 + text_width + border_width * 2;

	cairo_set_source_u32(cairo, box_colors.background);
	cairo_rectangle(cairo, *x, 0, width, height);
	cairo_fill(cairo);

	cairo_set_source_u32(cairo, box_colors.border);
	cairo_rectangle(cairo, *x, 0, width, border_width);
	cairo_fill(cairo);
	cairo_rectangle(cairo, *x, 0, border_width, height);
	cairo_fill(cairo);
	cairo_rectangle(cairo, *x + width - border_width, 0, border_width, height);
	cairo_fill(cairo);
	cairo_rectangle(cairo, *x, height - border_width, width, border_width);
	cairo_fill(cairo);

	double text_y = height / 2.0 - text_height / 2.0;
	cairo_set_source_u32(cairo, box_colors.text);
	cairo_move_to(cairo, *x + width / 2 - text_width / 2, (int)floor(text_y));
	pango_printf(cairo, config->font, output->scale, config->pango_markup,
			"%s", ws->label);

	struct swaybar_hotspot *hotspot = calloc(1, sizeof(struct swaybar_hotspot));
	hotspot->x = *x;
	hotspot->y = 0;
	hotspot->width = width;
	hotspot->height = height;
	hotspot->callback = workspace_hotspot_callback;
	hotspot->destroy = free;
	hotspot->data = strdup(ws->name);
	wl_list_insert(&output->hotspots, &hotspot->link);

	*x += width;
	return output->height;
}