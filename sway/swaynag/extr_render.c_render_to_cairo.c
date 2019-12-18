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
struct TYPE_5__ {scalar_t__ visible; } ;
struct swaynag {int width; int scale; scalar_t__ height; TYPE_3__* type; TYPE_2__ details; TYPE_1__* buttons; } ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_6__ {int button_margin_right; int button_gap; int button_gap_close; int bar_border_thickness; int /*<<< orphan*/  border_bottom; int /*<<< orphan*/  background; } ;
struct TYPE_4__ {int length; } ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_OPERATOR_SOURCE ; 
 int /*<<< orphan*/  cairo_fill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_paint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_rectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  cairo_set_operator (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_source_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ render_button (int /*<<< orphan*/ *,struct swaynag*,int,int*) ; 
 scalar_t__ render_detailed (int /*<<< orphan*/ *,struct swaynag*,scalar_t__) ; 
 scalar_t__ render_message (int /*<<< orphan*/ *,struct swaynag*) ; 

__attribute__((used)) static uint32_t render_to_cairo(cairo_t *cairo, struct swaynag *swaynag) {
	uint32_t max_height = 0;

	cairo_set_operator(cairo, CAIRO_OPERATOR_SOURCE);
	cairo_set_source_u32(cairo, swaynag->type->background);
	cairo_paint(cairo);

	uint32_t h = render_message(cairo, swaynag);
	max_height = h > max_height ? h : max_height;

	int x = swaynag->width - swaynag->type->button_margin_right;
	x *= swaynag->scale;
	for (int i = 0; i < swaynag->buttons->length; i++) {
		h = render_button(cairo, swaynag, i, &x);
		max_height = h > max_height ? h : max_height;
		x -= swaynag->type->button_gap * swaynag->scale;
		if (i == 0) {
			x -= swaynag->type->button_gap_close * swaynag->scale;
		}
	}

	if (swaynag->details.visible) {
		h = render_detailed(cairo, swaynag, max_height);
		max_height = h > max_height ? h : max_height;
	}

	int border = swaynag->type->bar_border_thickness * swaynag->scale;
	if (max_height > swaynag->height) {
		max_height += border;
	}
	cairo_set_source_u32(cairo, swaynag->type->border_bottom);
	cairo_rectangle(cairo, 0,
			swaynag->height * swaynag->scale - border,
			swaynag->width * swaynag->scale,
			border);
	cairo_fill(cairo);

	return max_height;
}