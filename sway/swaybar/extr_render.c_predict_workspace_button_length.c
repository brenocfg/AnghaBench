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
struct swaybar_workspace {int /*<<< orphan*/  label; } ;
struct swaybar_output {int scale; scalar_t__ height; TYPE_1__* bar; } ;
struct swaybar_config {int /*<<< orphan*/  height; int /*<<< orphan*/  pango_markup; int /*<<< orphan*/  font; } ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_2__ {struct swaybar_config* config; } ;

/* Variables and functions */
 int BORDER_WIDTH ; 
 int WS_HORIZONTAL_PADDING ; 
 int WS_VERTICAL_PADDING ; 
 int /*<<< orphan*/  get_text_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t predict_workspace_button_length(cairo_t *cairo,
		struct swaybar_output *output,
		struct swaybar_workspace *ws) {
	struct swaybar_config *config = output->bar->config;

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
		return 0;
	}

	return ws_horizontal_padding * 2 + text_width + border_width * 2;
}