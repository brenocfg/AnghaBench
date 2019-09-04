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
typedef  enum wl_output_transform { ____Placeholder_wl_output_transform } wl_output_transform ;

/* Variables and functions */
#define  WL_OUTPUT_TRANSFORM_180 135 
#define  WL_OUTPUT_TRANSFORM_270 134 
#define  WL_OUTPUT_TRANSFORM_90 133 
#define  WL_OUTPUT_TRANSFORM_FLIPPED 132 
#define  WL_OUTPUT_TRANSFORM_FLIPPED_180 131 
#define  WL_OUTPUT_TRANSFORM_FLIPPED_270 130 
#define  WL_OUTPUT_TRANSFORM_FLIPPED_90 129 
#define  WL_OUTPUT_TRANSFORM_NORMAL 128 

__attribute__((used)) static const char *ipc_json_output_transform_description(enum wl_output_transform transform) {
	switch (transform) {
	case WL_OUTPUT_TRANSFORM_NORMAL:
		return "normal";
	case WL_OUTPUT_TRANSFORM_90:
		return "90";
	case WL_OUTPUT_TRANSFORM_180:
		return "180";
	case WL_OUTPUT_TRANSFORM_270:
		return "270";
	case WL_OUTPUT_TRANSFORM_FLIPPED:
		return "flipped";
	case WL_OUTPUT_TRANSFORM_FLIPPED_90:
		return "flipped-90";
	case WL_OUTPUT_TRANSFORM_FLIPPED_180:
		return "flipped-180";
	case WL_OUTPUT_TRANSFORM_FLIPPED_270:
		return "flipped-270";
	}
	return NULL;
}