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
struct swaybar_config {double status_padding; int status_edge_padding; int /*<<< orphan*/  height; int /*<<< orphan*/ * sep_symbol; int /*<<< orphan*/  font; } ;
struct i3bar_block {int markup; int min_width; int border_left; int border_right; int separator_block_width; scalar_t__ urgent; scalar_t__ border; int /*<<< orphan*/ * min_width_str; int /*<<< orphan*/ * full_text; } ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_2__ {struct swaybar_config* config; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_text_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,int,int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void predict_status_block_pos(cairo_t *cairo,
		struct swaybar_output *output, struct i3bar_block *block, double *x,
		bool edge) {
	if (!block->full_text || !*block->full_text) {
		return;
	}

	struct swaybar_config *config = output->bar->config;

	int text_width, text_height;
	get_text_size(cairo, config->font, &text_width, &text_height, NULL,
			output->scale, block->markup, "%s", block->full_text);

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

	uint32_t ideal_height = text_height + ws_vertical_padding * 2;
	uint32_t ideal_surface_height = ideal_height / output->scale;
	if (!output->bar->config->height &&
			output->height < ideal_surface_height) {
		return;
	}

	*x -= width;
	if ((block->border || block->urgent) && block->border_left > 0) {
		*x -= (block->border_left * output->scale + margin);
	}
	if ((block->border || block->urgent) && block->border_right > 0) {
		*x -= (block->border_right * output->scale + margin);
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
				return;
			}
			if (sep_width > sep_block_width) {
				sep_block_width = sep_width + margin * 2;
			}
		}
		*x -= sep_block_width;
	} else if (config->status_edge_padding) {
		*x -= config->status_edge_padding * output->scale;
	}
}