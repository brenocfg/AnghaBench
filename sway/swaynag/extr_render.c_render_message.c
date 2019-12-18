#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct swaynag {int scale; scalar_t__ height; int /*<<< orphan*/  message; TYPE_1__* type; } ;
typedef  int /*<<< orphan*/  cairo_t ;
struct TYPE_2__ {int message_padding; int /*<<< orphan*/  font; int /*<<< orphan*/  text; } ;

/* Variables and functions */
 int /*<<< orphan*/  cairo_move_to (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  cairo_set_source_u32 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_text_size (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*,int*,int /*<<< orphan*/ *,int,int,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pango_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,int,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static uint32_t render_message(cairo_t *cairo, struct swaynag *swaynag) {
	int text_width, text_height;
	get_text_size(cairo, swaynag->type->font, &text_width, &text_height, NULL,
			swaynag->scale, true, "%s", swaynag->message);

	int padding = swaynag->type->message_padding * swaynag->scale;

	uint32_t ideal_height = text_height + padding * 2;
	uint32_t ideal_surface_height = ideal_height / swaynag->scale;
	if (swaynag->height < ideal_surface_height) {
		return ideal_surface_height;
	}

	cairo_set_source_u32(cairo, swaynag->type->text);
	cairo_move_to(cairo, padding, (int)(ideal_height - text_height) / 2);
	pango_printf(cairo, swaynag->type->font, swaynag->scale, false,
			"%s", swaynag->message);

	return ideal_surface_height;
}