#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  text; } ;
struct TYPE_5__ {int /*<<< orphan*/  text; } ;
struct TYPE_7__ {TYPE_2__ button_down; TYPE_1__ button_up; } ;
struct swaynag {int scale; TYPE_4__* type; TYPE_3__ details; } ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_8__ {int button_border_thickness; int button_padding; int /*<<< orphan*/  font; } ;

/* Variables and functions */
 int /*<<< orphan*/  get_text_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,int,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int get_detailed_scroll_button_width(cairo_t *cairo,
		struct swaynag *swaynag) {
	int up_width, down_width, temp_height;
	get_text_size(cairo, swaynag->type->font, &up_width, &temp_height, NULL,
			swaynag->scale, true,
			"%s", swaynag->details.button_up.text);
	get_text_size(cairo, swaynag->type->font, &down_width, &temp_height, NULL,
			swaynag->scale, true,
			"%s", swaynag->details.button_down.text);

	int text_width =  up_width > down_width ? up_width : down_width;
	int border = swaynag->type->button_border_thickness * swaynag->scale;
	int padding = swaynag->type->button_padding * swaynag->scale;

	return text_width + border * 2 + padding * 2;
}