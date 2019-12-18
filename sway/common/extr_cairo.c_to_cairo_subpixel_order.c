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
typedef  enum wl_output_subpixel { ____Placeholder_wl_output_subpixel } wl_output_subpixel ;
typedef  int /*<<< orphan*/  cairo_subpixel_order_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAIRO_SUBPIXEL_ORDER_BGR ; 
 int /*<<< orphan*/  CAIRO_SUBPIXEL_ORDER_DEFAULT ; 
 int /*<<< orphan*/  CAIRO_SUBPIXEL_ORDER_RGB ; 
 int /*<<< orphan*/  CAIRO_SUBPIXEL_ORDER_VBGR ; 
 int /*<<< orphan*/  CAIRO_SUBPIXEL_ORDER_VRGB ; 
#define  WL_OUTPUT_SUBPIXEL_HORIZONTAL_BGR 131 
#define  WL_OUTPUT_SUBPIXEL_HORIZONTAL_RGB 130 
#define  WL_OUTPUT_SUBPIXEL_VERTICAL_BGR 129 
#define  WL_OUTPUT_SUBPIXEL_VERTICAL_RGB 128 

cairo_subpixel_order_t to_cairo_subpixel_order(enum wl_output_subpixel subpixel) {
	switch (subpixel) {
	case WL_OUTPUT_SUBPIXEL_HORIZONTAL_RGB:
		return CAIRO_SUBPIXEL_ORDER_RGB;
	case WL_OUTPUT_SUBPIXEL_HORIZONTAL_BGR:
		return CAIRO_SUBPIXEL_ORDER_BGR;
	case WL_OUTPUT_SUBPIXEL_VERTICAL_RGB:
		return CAIRO_SUBPIXEL_ORDER_VRGB;
	case WL_OUTPUT_SUBPIXEL_VERTICAL_BGR:
		return CAIRO_SUBPIXEL_ORDER_VBGR;
	default:
		return CAIRO_SUBPIXEL_ORDER_DEFAULT;
	}
	return CAIRO_SUBPIXEL_ORDER_DEFAULT;
}