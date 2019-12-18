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
struct swaynag_type {int anchors; int button_background; int background; int text; int border; int border_bottom; int bar_border_thickness; int message_padding; int details_border_thickness; int button_border_thickness; int button_gap; int button_gap_close; int button_margin_right; int button_padding; int /*<<< orphan*/  font; } ;
typedef  int /*<<< orphan*/  list_t ;

/* Variables and functions */
 int ZWLR_LAYER_SURFACE_V1_ANCHOR_LEFT ; 
 int ZWLR_LAYER_SURFACE_V1_ANCHOR_RIGHT ; 
 int ZWLR_LAYER_SURFACE_V1_ANCHOR_TOP ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,struct swaynag_type*) ; 
 int /*<<< orphan*/  strdup (char*) ; 
 struct swaynag_type* swaynag_type_new (char*) ; 

void swaynag_types_add_default(list_t *types) {
	struct swaynag_type *type_defaults = swaynag_type_new("<defaults>");
	type_defaults->font = strdup("pango:Monospace 10");
	type_defaults->anchors = ZWLR_LAYER_SURFACE_V1_ANCHOR_TOP
		| ZWLR_LAYER_SURFACE_V1_ANCHOR_LEFT
		| ZWLR_LAYER_SURFACE_V1_ANCHOR_RIGHT;
	type_defaults->button_background = 0x333333FF;
	type_defaults->background = 0x323232FF;
	type_defaults->text = 0xFFFFFFFF;
	type_defaults->border = 0x222222FF;
	type_defaults->border_bottom = 0x444444FF;
	type_defaults->bar_border_thickness = 2;
	type_defaults->message_padding = 8;
	type_defaults->details_border_thickness = 3;
	type_defaults->button_border_thickness = 3;
	type_defaults->button_gap = 20;
	type_defaults->button_gap_close = 15;
	type_defaults->button_margin_right = 2;
	type_defaults->button_padding = 3;
	list_add(types, type_defaults);

	struct swaynag_type *type_error = swaynag_type_new("error");
	type_error->button_background = 0x680A0AFF;
	type_error->background = 0x900000FF;
	type_error->text = 0xFFFFFFFF;
	type_error->border = 0xD92424FF;
	type_error->border_bottom = 0x470909FF;
	list_add(types, type_error);

	struct swaynag_type *type_warning = swaynag_type_new("warning");
	type_warning->button_background = 0xFFC100FF;
	type_warning->background = 0xFFA800FF;
	type_warning->text = 0x000000FF;
	type_warning->border = 0xAB7100FF;
	type_warning->border_bottom = 0xAB7100FF;
	list_add(types, type_warning);
}