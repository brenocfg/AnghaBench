#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int uint32_t ;
struct TYPE_9__ {int x; int y; int width; int height; } ;
struct TYPE_7__ {int x; int y; int width; int height; TYPE_4__ button_down; TYPE_4__ button_up; void* visible_lines; int /*<<< orphan*/  offset; void* total_lines; int /*<<< orphan*/  message; } ;
struct swaynag {int width; int scale; TYPE_1__* type; TYPE_2__ details; } ;
typedef  int gint ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_8__ {int start_index; } ;
struct TYPE_6__ {int details_border_thickness; int message_padding; int /*<<< orphan*/  text; int /*<<< orphan*/  border; int /*<<< orphan*/  font; } ;
typedef  TYPE_3__ PangoLayoutLine ;
typedef  int /*<<< orphan*/  PangoLayout ;

/* Variables and functions */
 int /*<<< orphan*/  PANGO_ELLIPSIZE_END ; 
 int PANGO_SCALE ; 
 int /*<<< orphan*/  PANGO_WRAP_WORD_CHAR ; 
 int SWAYNAG_MAX_HEIGHT ; 
 int /*<<< orphan*/  cairo_fill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_move_to (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cairo_rectangle (int /*<<< orphan*/ *,int,int,int,int) ; 
 int /*<<< orphan*/  cairo_set_source_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int get_detailed_scroll_button_width (int /*<<< orphan*/ *,struct swaynag*) ; 
 int /*<<< orphan*/ * get_pango_layout (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pango_cairo_show_layout (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_cairo_update_layout (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 void* pango_layout_get_line_count (int /*<<< orphan*/ *) ; 
 TYPE_3__* pango_layout_get_line_readonly (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_layout_get_pixel_size (int /*<<< orphan*/ *,int*,int*) ; 
 char* pango_layout_get_text (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pango_layout_set_ellipsize (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_layout_set_height (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pango_layout_set_single_paragraph_mode (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pango_layout_set_text (int /*<<< orphan*/ *,char const*,int) ; 
 int /*<<< orphan*/  pango_layout_set_width (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  pango_layout_set_wrap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  render_details_scroll_button (int /*<<< orphan*/ *,struct swaynag*,TYPE_4__*) ; 
 int strlen (char const*) ; 

__attribute__((used)) static uint32_t render_detailed(cairo_t *cairo, struct swaynag *swaynag,
		uint32_t y) {
	uint32_t width = swaynag->width * swaynag->scale;

	int border = swaynag->type->details_border_thickness * swaynag->scale;
	int padding = swaynag->type->message_padding * swaynag->scale;
	int decor = padding + border;

	swaynag->details.x = decor;
	swaynag->details.y = y * swaynag->scale + decor;
	swaynag->details.width = width - decor * 2;

	PangoLayout *layout = get_pango_layout(cairo, swaynag->type->font,
			swaynag->details.message, swaynag->scale, false);
	pango_layout_set_width(layout,
			(swaynag->details.width - padding * 2) * PANGO_SCALE);
	pango_layout_set_wrap(layout, PANGO_WRAP_WORD_CHAR);
	pango_layout_set_single_paragraph_mode(layout, false);
	pango_cairo_update_layout(cairo, layout);
	swaynag->details.total_lines = pango_layout_get_line_count(layout);

	PangoLayoutLine *line;
	line = pango_layout_get_line_readonly(layout, swaynag->details.offset);
	gint offset = line->start_index;
	const char *text = pango_layout_get_text(layout);
	pango_layout_set_text(layout, text + offset, strlen(text) - offset);

	int text_width, text_height;
	pango_cairo_update_layout(cairo, layout);
	pango_layout_get_pixel_size(layout, &text_width, &text_height);

	bool show_buttons = swaynag->details.offset > 0;
	int button_width = get_detailed_scroll_button_width(cairo, swaynag);
	if (show_buttons) {
		swaynag->details.width -= button_width;
		pango_layout_set_width(layout,
				(swaynag->details.width - padding * 2) * PANGO_SCALE);
	}

	uint32_t ideal_height;
	do {
		ideal_height = swaynag->details.y + text_height + decor + padding * 2;
		if (ideal_height > SWAYNAG_MAX_HEIGHT) {
			ideal_height = SWAYNAG_MAX_HEIGHT;

			if (!show_buttons) {
				show_buttons = true;
				swaynag->details.width -= button_width;
				pango_layout_set_width(layout,
						(swaynag->details.width - padding * 2) * PANGO_SCALE);
			}
		}

		swaynag->details.height = ideal_height - swaynag->details.y - decor;
		pango_layout_set_height(layout,
				(swaynag->details.height - padding * 2) * PANGO_SCALE);
		pango_layout_set_ellipsize(layout, PANGO_ELLIPSIZE_END);
		pango_cairo_update_layout(cairo, layout);
		pango_layout_get_pixel_size(layout, &text_width, &text_height);
	} while (text_height != (swaynag->details.height - padding * 2));

	swaynag->details.visible_lines = pango_layout_get_line_count(layout);

	if (show_buttons) {
		swaynag->details.button_up.x =
			swaynag->details.x + swaynag->details.width;
		swaynag->details.button_up.y = swaynag->details.y;
		swaynag->details.button_up.width = button_width;
		swaynag->details.button_up.height = swaynag->details.height / 2;
		render_details_scroll_button(cairo, swaynag,
				&swaynag->details.button_up);

		swaynag->details.button_down.x =
			swaynag->details.x + swaynag->details.width;
		swaynag->details.button_down.y =
			swaynag->details.button_up.y + swaynag->details.button_up.height;
		swaynag->details.button_down.width = button_width;
		swaynag->details.button_down.height = swaynag->details.height / 2;
		render_details_scroll_button(cairo, swaynag,
				&swaynag->details.button_down);
	}

	cairo_set_source_u32(cairo, swaynag->type->border);
	cairo_rectangle(cairo, swaynag->details.x, swaynag->details.y,
			swaynag->details.width, swaynag->details.height);
	cairo_fill(cairo);

	cairo_move_to(cairo, swaynag->details.x + padding,
			swaynag->details.y + padding);
	cairo_set_source_u32(cairo, swaynag->type->text);
	pango_cairo_show_layout(cairo, layout);
	g_object_unref(layout);

	return ideal_height / swaynag->scale;
}