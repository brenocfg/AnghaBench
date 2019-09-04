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

/* Variables and functions */
#define  WL_OUTPUT_SUBPIXEL_HORIZONTAL_BGR 133 
#define  WL_OUTPUT_SUBPIXEL_HORIZONTAL_RGB 132 
#define  WL_OUTPUT_SUBPIXEL_NONE 131 
#define  WL_OUTPUT_SUBPIXEL_UNKNOWN 130 
#define  WL_OUTPUT_SUBPIXEL_VERTICAL_BGR 129 
#define  WL_OUTPUT_SUBPIXEL_VERTICAL_RGB 128 
 int /*<<< orphan*/  sway_assert (int,char*) ; 

const char *sway_wl_output_subpixel_to_string(enum wl_output_subpixel subpixel) {
	switch (subpixel) {
	case WL_OUTPUT_SUBPIXEL_UNKNOWN:
		return "unknown";
	case WL_OUTPUT_SUBPIXEL_NONE:
		return "none";
	case WL_OUTPUT_SUBPIXEL_HORIZONTAL_RGB:
		return "rgb";
	case WL_OUTPUT_SUBPIXEL_HORIZONTAL_BGR:
		return "bgr";
	case WL_OUTPUT_SUBPIXEL_VERTICAL_RGB:
		return "vrgb";
	case WL_OUTPUT_SUBPIXEL_VERTICAL_BGR:
		return "vbgr";
	}
	sway_assert(false, "Unknown value for wl_output_subpixel.");
	return NULL;
}