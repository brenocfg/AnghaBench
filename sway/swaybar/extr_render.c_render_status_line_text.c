#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct swaybar_output {double scale; scalar_t__ height; TYPE_3__* bar; scalar_t__ focused; } ;
struct TYPE_5__ {int /*<<< orphan*/  statusline; int /*<<< orphan*/  focused_statusline; } ;
struct swaybar_config {double status_padding; int /*<<< orphan*/  pango_markup; int /*<<< orphan*/  font; int /*<<< orphan*/  height; TYPE_2__ colors; } ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_6__ {struct swaybar_config* config; TYPE_1__* status; } ;
struct TYPE_4__ {char* text; } ;

/* Variables and functions */
 int /*<<< orphan*/  cairo_move_to (int /*<<< orphan*/ *,double,int) ; 
 int /*<<< orphan*/  cairo_set_source_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ floor (double) ; 
 int /*<<< orphan*/  get_text_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,double,int /*<<< orphan*/ ,char*,char const*) ; 
 int /*<<< orphan*/  pango_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static uint32_t render_status_line_text(cairo_t *cairo,
		struct swaybar_output *output, double *x) {
	const char *text = output->bar->status->text;
	if (!text) {
		return 0;
	}

	struct swaybar_config *config = output->bar->config;
	cairo_set_source_u32(cairo, output->focused ?
			config->colors.focused_statusline : config->colors.statusline);

	int text_width, text_height;
	get_text_size(cairo, config->font, &text_width, &text_height, NULL,
			output->scale, config->pango_markup, "%s", text);

	double ws_vertical_padding = config->status_padding * output->scale;
	int margin = 3 * output->scale;

	uint32_t ideal_height = text_height + ws_vertical_padding * 2;
	uint32_t ideal_surface_height = ideal_height / output->scale;
	if (!output->bar->config->height &&
			output->height < ideal_surface_height) {
		return ideal_surface_height;
	}

	*x -= text_width + margin;
	uint32_t height = output->height * output->scale;
	double text_y = height / 2.0 - text_height / 2.0;
	cairo_move_to(cairo, *x, (int)floor(text_y));
	pango_printf(cairo, config->font, output->scale,
			config->pango_markup, "%s", text);
	*x -= margin;
	return output->height;
}