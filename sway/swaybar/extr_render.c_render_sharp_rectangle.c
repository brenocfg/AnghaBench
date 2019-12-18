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
 int /*<<< orphan*/  cairo_fill (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_rectangle (int /*<<< orphan*/ *,double,double,double,double) ; 
 int /*<<< orphan*/  cairo_restore (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_save (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_set_antialias (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cairo_set_source_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void render_sharp_rectangle(cairo_t *cairo, uint32_t color,
		double x, double y, double width, double height) {
	cairo_save(cairo);
	cairo_set_source_u32(cairo, color);
	cairo_set_antialias(cairo, CAIRO_ANTIALIAS_NONE);
	cairo_rectangle(cairo, x, y, width, height);
	cairo_fill(cairo);
	cairo_restore(cairo);
}