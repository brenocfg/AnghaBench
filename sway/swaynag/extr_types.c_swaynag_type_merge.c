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
struct swaynag_type {scalar_t__ anchors; scalar_t__ button_background; scalar_t__ background; scalar_t__ text; scalar_t__ border; scalar_t__ border_bottom; int bar_border_thickness; int message_padding; int details_border_thickness; int button_border_thickness; int button_gap; int button_gap_close; int button_margin_right; int button_padding; void* output; void* font; } ;

/* Variables and functions */
 void* strdup (void*) ; 

void swaynag_type_merge(struct swaynag_type *dest, struct swaynag_type *src) {
	if (!dest || !src) {
		return;
	}

	if (src->font) {
		dest->font = strdup(src->font);
	}

	if (src->output) {
		dest->output = strdup(src->output);
	}

	if (src->anchors > 0) {
		dest->anchors = src->anchors;
	}

	// Colors
	if (src->button_background > 0) {
		dest->button_background = src->button_background;
	}

	if (src->background > 0) {
		dest->background = src->background;
	}

	if (src->text > 0) {
		dest->text = src->text;
	}

	if (src->border > 0) {
		dest->border = src->border;
	}

	if (src->border_bottom > 0) {
		dest->border_bottom = src->border_bottom;
	}

	// Sizing
	if (src->bar_border_thickness > -1) {
		dest->bar_border_thickness = src->bar_border_thickness;
	}

	if (src->message_padding > -1) {
		dest->message_padding = src->message_padding;
	}

	if (src->details_border_thickness > -1) {
		dest->details_border_thickness = src->details_border_thickness;
	}

	if (src->button_border_thickness > -1) {
		dest->button_border_thickness = src->button_border_thickness;
	}

	if (src->button_gap > -1) {
		dest->button_gap = src->button_gap;
	}

	if (src->button_gap_close > -1) {
		dest->button_gap_close = src->button_gap_close;
	}

	if (src->button_margin_right > -1) {
		dest->button_margin_right = src->button_margin_right;
	}

	if (src->button_padding > -1) {
		dest->button_padding = src->button_padding;
	}
}