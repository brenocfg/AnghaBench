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
struct swaynag_button {int height; int /*<<< orphan*/  text; scalar_t__ y; scalar_t__ x; scalar_t__ width; } ;
struct swaynag {int scale; TYPE_1__* type; } ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_2__ {int button_border_thickness; int button_padding; int /*<<< orphan*/  font; int /*<<< orphan*/  text; int /*<<< orphan*/  button_background; int /*<<< orphan*/  border; } ;

/* Variables and functions */
 int /*<<< orphan*/  cairo_fill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_move_to (int /*<<< orphan*/ *,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  cairo_rectangle (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int /*<<< orphan*/  cairo_set_source_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_text_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void render_details_scroll_button(cairo_t *cairo,
		struct swaynag *swaynag, struct swaynag_button *button) {
	int text_width, text_height;
	get_text_size(cairo, swaynag->type->font, &text_width, &text_height, NULL,
			swaynag->scale, true, "%s", button->text);

	int border = swaynag->type->button_border_thickness * swaynag->scale;
	int padding = swaynag->type->button_padding * swaynag->scale;

	cairo_set_source_u32(cairo, swaynag->type->border);
	cairo_rectangle(cairo, button->x, button->y,
			button->width, button->height);
	cairo_fill(cairo);

	cairo_set_source_u32(cairo, swaynag->type->button_background);
	cairo_rectangle(cairo, button->x + border, button->y + border,
			button->width - (border * 2), button->height - (border * 2));
	cairo_fill(cairo);

	cairo_set_source_u32(cairo, swaynag->type->text);
	cairo_move_to(cairo, button->x + border + padding,
			button->y + border + (button->height - text_height) / 2);
	pango_printf(cairo, swaynag->type->font, swaynag->scale, true,
			"%s", button->text);
}