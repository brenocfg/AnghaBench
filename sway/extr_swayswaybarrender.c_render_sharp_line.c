#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  cairo_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_ANTIALIAS_NONE ; 
 int /*<<< orphan*/  cairo_line_to (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  cairo_move_to (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  cairo_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_set_antialias (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_line_width (int /*<<< orphan*/ *,double) ; 
 int /*<<< orphan*/  cairo_set_source_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_stroke (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  render_sharp_rectangle (int /*<<< orphan*/ *,int /*<<< orphan*/ ,double,double,double,double) ; 

__attribute__((used)) static void render_sharp_line(cairo_t *cairo, uint32_t color,
		double x, double y, double width, double height) {
	if (width > 1 && height > 1) {
		render_sharp_rectangle(cairo, color, x, y, width, height);
	} else {
		cairo_save(cairo);
		cairo_set_source_u32(cairo, color);
		cairo_set_antialias(cairo, CAIRO_ANTIALIAS_NONE);
		if (width == 1) {
			x += 0.5;
			height += y;
			width = x;
		}
		if (height == 1) {
			y += 0.5;
			width += x;
			height = y;
		}
		cairo_move_to(cairo, x, y);
		cairo_set_line_width(cairo, 1.0);
		cairo_line_to(cairo, width, height);
		cairo_stroke(cairo);
		cairo_restore(cairo);
	}
}