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
struct swaybar_output {int scale; scalar_t__ height; TYPE_1__* bar; } ;
struct swaybar_config {int /*<<< orphan*/  height; int /*<<< orphan*/  font; int /*<<< orphan*/  binding_mode_indicator; } ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_2__ {char* mode; struct swaybar_config* config; int /*<<< orphan*/  mode_pango_markup; } ;

/* Variables and functions */
 int BORDER_WIDTH ; 
 int WS_HORIZONTAL_PADDING ; 
 int WS_VERTICAL_PADDING ; 
 int /*<<< orphan*/  get_text_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static uint32_t predict_binding_mode_indicator_length(cairo_t *cairo,
		struct swaybar_output *output) {
	const char *mode = output->bar->mode;
	if (!mode) {
		return 0;
	}

	struct swaybar_config *config = output->bar->config;

	if (!config->binding_mode_indicator) {
		return 0;
	}

	int text_width, text_height;
	get_text_size(cairo, config->font, &text_width, &text_height, NULL,
			output->scale, output->bar->mode_pango_markup,
			"%s", mode);

	int ws_vertical_padding = WS_VERTICAL_PADDING * output->scale;
	int ws_horizontal_padding = WS_HORIZONTAL_PADDING * output->scale;
	int border_width = BORDER_WIDTH * output->scale;

	uint32_t ideal_height = text_height + ws_vertical_padding * 2
		+ border_width * 2;
	uint32_t ideal_surface_height = ideal_height / output->scale;
	if (!output->bar->config->height &&
			output->height < ideal_surface_height) {
		return 0;
	}
	return text_width + ws_horizontal_padding * 2 + border_width * 2;
}