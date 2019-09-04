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
struct swaynag_button {int x; int y; int width; int height; int /*<<< orphan*/  text; } ;
struct swaynag {int scale; scalar_t__ height; TYPE_2__* type; TYPE_1__* buttons; } ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_4__ {int button_border_thickness; int button_padding; int /*<<< orphan*/  font; int /*<<< orphan*/  text; int /*<<< orphan*/  button_background; int /*<<< orphan*/  border; } ;
struct TYPE_3__ {struct swaynag_button** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  cairo_fill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_move_to (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cairo_rectangle (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  cairo_set_source_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_text_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t render_button(cairo_t *cairo, struct swaynag *swaynag,
		int button_index, int *x) {
	struct swaynag_button *button = swaynag->buttons->items[button_index];

	int text_width, text_height;
	get_text_size(cairo, swaynag->type->font, &text_width, &text_height, NULL,
			swaynag->scale, true, "%s", button->text);

	int border = swaynag->type->button_border_thickness * swaynag->scale;
	int padding = swaynag->type->button_padding * swaynag->scale;

	uint32_t ideal_height = text_height + padding * 2 + border * 2;
	uint32_t ideal_surface_height = ideal_height / swaynag->scale;
	if (swaynag->height < ideal_surface_height) {
		return ideal_surface_height;
	}

	button->x = *x - border - text_width - padding * 2 + 1;
	button->y = (int)(ideal_height - text_height) / 2 - padding + 1;
	button->width = text_width + padding * 2;
	button->height = text_height + padding * 2;

	cairo_set_source_u32(cairo, swaynag->type->border);
	cairo_rectangle(cairo, button->x - border, button->y - border,
			button->width + border * 2, button->height + border * 2);
	cairo_fill(cairo);

	cairo_set_source_u32(cairo, swaynag->type->button_background);
	cairo_rectangle(cairo, button->x, button->y,
			button->width, button->height);
	cairo_fill(cairo);

	cairo_set_source_u32(cairo, swaynag->type->text);
	cairo_move_to(cairo, button->x + padding, button->y + padding);
	pango_printf(cairo, swaynag->type->font, swaynag->scale, true,
			"%s", button->text);

	*x = button->x - border;

	return ideal_surface_height;
}