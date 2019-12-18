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
typedef  scalar_t__ uint32_t ;
struct swaybar_output {int scale; scalar_t__ height; scalar_t__ focused; int /*<<< orphan*/  hotspots; TYPE_4__* bar; } ;
struct swaybar_hotspot {double x; int width; int /*<<< orphan*/  link; struct i3bar_block* data; int /*<<< orphan*/  destroy; int /*<<< orphan*/  callback; scalar_t__ height; scalar_t__ y; } ;
struct TYPE_6__ {scalar_t__ background; scalar_t__ border; scalar_t__ text; } ;
struct TYPE_7__ {scalar_t__ statusline; scalar_t__ focused_separator; scalar_t__ separator; TYPE_2__ urgent_workspace; } ;
struct swaybar_config {double status_padding; char* sep_symbol; int status_edge_padding; int /*<<< orphan*/  font; TYPE_3__ colors; int /*<<< orphan*/  height; } ;
struct i3bar_block {char* full_text; char* short_text; int markup; char* min_width_str; int min_width; scalar_t__ border; int border_left; int border_right; int separator_block_width; scalar_t__ background; double border_top; double border_bottom; scalar_t__* color; scalar_t__ separator; scalar_t__ urgent; int /*<<< orphan*/  align; int /*<<< orphan*/  ref_count; } ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_8__ {TYPE_1__* status; struct swaybar_config* config; } ;
struct TYPE_5__ {scalar_t__ click_events; } ;

/* Variables and functions */
 int /*<<< orphan*/  block_hotspot_callback ; 
 int /*<<< orphan*/  cairo_line_to (int /*<<< orphan*/ *,double,scalar_t__) ; 
 int /*<<< orphan*/  cairo_move_to (int /*<<< orphan*/ *,double,int) ; 
 int /*<<< orphan*/  cairo_set_line_width (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cairo_set_source_u32 (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cairo_stroke (int /*<<< orphan*/ *) ; 
 struct swaybar_hotspot* calloc (int,int) ; 
 scalar_t__ floor (double) ; 
 int /*<<< orphan*/  get_text_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,int,int,char*,char*) ; 
 int /*<<< orphan*/  i3bar_block_unref_callback ; 
 int /*<<< orphan*/  pango_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,char*,char*) ; 
 int /*<<< orphan*/  render_sharp_line (int /*<<< orphan*/ *,scalar_t__,double,double,double,double) ; 
 int /*<<< orphan*/  render_sharp_rectangle (int /*<<< orphan*/ *,scalar_t__,double,double,double,double) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wl_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint32_t render_status_block(cairo_t *cairo,
		struct swaybar_output *output, struct i3bar_block *block, double *x,
		bool edge, bool use_short_text) {
	if (!block->full_text || !*block->full_text) {
		return 0;
	}

	char* text = block->full_text;
	if (use_short_text && block->short_text && *block->short_text) {
		text = block->short_text;
	}

	struct swaybar_config *config = output->bar->config;

	int text_width, text_height;
	get_text_size(cairo, config->font, &text_width, &text_height, NULL,
			output->scale, block->markup, "%s", text);

	int margin = 3 * output->scale;
	double ws_vertical_padding = config->status_padding * output->scale;

	int width = text_width;
	if (block->min_width_str) {
		int w;
		get_text_size(cairo, config->font, &w, NULL, NULL,
				output->scale, block->markup, "%s", block->min_width_str);
		block->min_width = w;
	}
	if (width < block->min_width) {
		width = block->min_width;
	}

	double block_width = width;
	uint32_t ideal_height = text_height + ws_vertical_padding * 2;
	uint32_t ideal_surface_height = ideal_height / output->scale;
	if (!output->bar->config->height &&
			output->height < ideal_surface_height) {
		return ideal_surface_height;
	}

	*x -= width;
	if ((block->border || block->urgent) && block->border_left > 0) {
		*x -= (block->border_left * output->scale + margin);
		block_width += block->border_left * output->scale + margin;
	}
	if ((block->border || block->urgent) && block->border_right > 0) {
		*x -= (block->border_right * output->scale + margin);
		block_width += block->border_right * output->scale + margin;
	}

	int sep_width, sep_height;
	int sep_block_width = block->separator_block_width;
	if (!edge) {
		if (config->sep_symbol) {
			get_text_size(cairo, config->font, &sep_width, &sep_height, NULL,
					output->scale, false, "%s", config->sep_symbol);
			uint32_t _ideal_height = sep_height + ws_vertical_padding * 2;
			uint32_t _ideal_surface_height = _ideal_height / output->scale;
			if (!output->bar->config->height &&
					output->height < _ideal_surface_height) {
				return _ideal_surface_height;
			}
			if (sep_width > sep_block_width) {
				sep_block_width = sep_width + margin * 2;
			}
		}
		*x -= sep_block_width;
	} else if (config->status_edge_padding) {
		*x -= config->status_edge_padding * output->scale;
	}

	uint32_t height = output->height * output->scale;
	if (output->bar->status->click_events) {
		struct swaybar_hotspot *hotspot = calloc(1, sizeof(struct swaybar_hotspot));
		hotspot->x = *x;
		hotspot->y = 0;
		hotspot->width = width;
		hotspot->height = height;
		hotspot->callback = block_hotspot_callback;
		hotspot->destroy = i3bar_block_unref_callback;
		hotspot->data = block;
		block->ref_count++;
		wl_list_insert(&output->hotspots, &hotspot->link);
	}

	double x_pos = *x;
	double y_pos = ws_vertical_padding;
	double render_height = height - ws_vertical_padding * 2;

	uint32_t bg_color = block->urgent
		? config->colors.urgent_workspace.background : block->background;
	if (bg_color) {
		render_sharp_rectangle(cairo, bg_color, x_pos, y_pos,
				block_width, render_height);
	}

	uint32_t border_color = block->urgent
		? config->colors.urgent_workspace.border : block->border;
	if (border_color && block->border_top > 0) {
		render_sharp_line(cairo, border_color, x_pos, y_pos,
				block_width, block->border_top * output->scale);
	}
	if (border_color && block->border_bottom > 0) {
		render_sharp_line(cairo, border_color, x_pos,
				y_pos + render_height - block->border_bottom * output->scale,
				block_width, block->border_bottom * output->scale);
	}
	if (border_color && block->border_left > 0) {
		render_sharp_line(cairo, border_color, x_pos, y_pos,
				block->border_left * output->scale, render_height);
		x_pos += block->border_left * output->scale + margin;
	}

	double offset = 0;
	if (strncmp(block->align, "left", 5) == 0) {
		offset = x_pos;
	} else if (strncmp(block->align, "right", 5) == 0) {
		offset = x_pos + width - text_width;
	} else if (strncmp(block->align, "center", 6) == 0) {
		offset = x_pos + (width - text_width) / 2;
	}
	double text_y = height / 2.0 - text_height / 2.0;
	cairo_move_to(cairo, offset, (int)floor(text_y));
	uint32_t color = block->color ?  *block->color : config->colors.statusline;
	color = block->urgent ? config->colors.urgent_workspace.text : color;
	cairo_set_source_u32(cairo, color);
	pango_printf(cairo, config->font, output->scale,
			block->markup, "%s", text);
	x_pos += width;

	if (block->border && block->border_right > 0) {
		x_pos += margin;
		render_sharp_line(cairo, border_color, x_pos, y_pos,
				block->border_right * output->scale, render_height);
		x_pos += block->border_right * output->scale;
	}

	if (!edge && block->separator) {
		if (output->focused) {
			cairo_set_source_u32(cairo, config->colors.focused_separator);
		} else {
			cairo_set_source_u32(cairo, config->colors.separator);
		}
		if (config->sep_symbol) {
			offset = x_pos + (sep_block_width - sep_width) / 2;
			double sep_y = height / 2.0 - sep_height / 2.0;
			cairo_move_to(cairo, offset, (int)floor(sep_y));
			pango_printf(cairo, config->font, output->scale, false,
					"%s", config->sep_symbol);
		} else {
			cairo_set_line_width(cairo, 1);
			cairo_move_to(cairo, x_pos + sep_block_width / 2, margin);
			cairo_line_to(cairo, x_pos + sep_block_width / 2, height - margin);
			cairo_stroke(cairo);
		}
	}
	return output->height;
}