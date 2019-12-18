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
typedef  int /*<<< orphan*/  cairo_t ;
typedef  int /*<<< orphan*/  cairo_surface_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_FORMAT_ARGB32 ; 
 int /*<<< orphan*/ * cairo_create (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * cairo_image_surface_create (int /*<<< orphan*/ ,int,int) ; 
 int cairo_image_surface_get_height (int /*<<< orphan*/ *) ; 
 int cairo_image_surface_get_width (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_paint (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cairo_scale (int /*<<< orphan*/ *,double,double) ; 
 int /*<<< orphan*/  cairo_set_source_surface (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

cairo_surface_t *cairo_image_surface_scale(cairo_surface_t *image,
		int width, int height) {
	int image_width = cairo_image_surface_get_width(image);
	int image_height = cairo_image_surface_get_height(image);

	cairo_surface_t *new =
		cairo_image_surface_create(CAIRO_FORMAT_ARGB32, width, height);
	cairo_t *cairo = cairo_create(new);
	cairo_scale(cairo, (double)width / image_width,
			(double)height / image_height);
	cairo_set_source_surface(cairo, image, 0, 0);

	cairo_paint(cairo);
	cairo_destroy(cairo);
	return new;
}