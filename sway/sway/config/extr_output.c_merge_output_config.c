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
struct output_config {int enabled; int width; int height; int x; int y; int scale; scalar_t__ subpixel; int refresh_rate; int custom_mode; int transform; scalar_t__ dpms_state; void* background_fallback; void* background_option; void* background; } ;

/* Variables and functions */
 scalar_t__ WL_OUTPUT_SUBPIXEL_UNKNOWN ; 
 int /*<<< orphan*/  free (void*) ; 
 void* strdup (void*) ; 

void merge_output_config(struct output_config *dst, struct output_config *src) {
	if (src->enabled != -1) {
		dst->enabled = src->enabled;
	}
	if (src->width != -1) {
		dst->width = src->width;
	}
	if (src->height != -1) {
		dst->height = src->height;
	}
	if (src->x != -1) {
		dst->x = src->x;
	}
	if (src->y != -1) {
		dst->y = src->y;
	}
	if (src->scale != -1) {
		dst->scale = src->scale;
	}
	if (src->subpixel != WL_OUTPUT_SUBPIXEL_UNKNOWN) {
		dst->subpixel = src->subpixel;
	}
	if (src->refresh_rate != -1) {
		dst->refresh_rate = src->refresh_rate;
	}
	if (src->custom_mode != -1) {
		dst->custom_mode = src->custom_mode;
	}
	if (src->transform != -1) {
		dst->transform = src->transform;
	}
	if (src->background) {
		free(dst->background);
		dst->background = strdup(src->background);
	}
	if (src->background_option) {
		free(dst->background_option);
		dst->background_option = strdup(src->background_option);
	}
	if (src->background_fallback) {
		free(dst->background_fallback);
		dst->background_fallback = strdup(src->background_fallback);
	}
	if (src->dpms_state != 0) {
		dst->dpms_state = src->dpms_state;
	}
}