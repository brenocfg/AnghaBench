#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct wlr_keyboard {int dummy; } ;
struct sway_seat {int /*<<< orphan*/  wlr_seat; TYPE_2__* cursor; struct seatop_resize_floating_event* seatop_data; int /*<<< orphan*/ * seatop_impl; } ;
struct sway_container {int /*<<< orphan*/  height; int /*<<< orphan*/  width; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
struct seatop_resize_floating_event {int edge; int /*<<< orphan*/  ref_height; int /*<<< orphan*/  ref_width; int /*<<< orphan*/  ref_con_ly; int /*<<< orphan*/  ref_con_lx; int /*<<< orphan*/  ref_ly; int /*<<< orphan*/  ref_lx; int /*<<< orphan*/  preserve_ratio; struct sway_container* con; } ;
typedef  enum wlr_edges { ____Placeholder_wlr_edges } wlr_edges ;
struct TYPE_4__ {TYPE_1__* cursor; } ;
struct TYPE_3__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int WLR_EDGE_BOTTOM ; 
 int WLR_EDGE_NONE ; 
 int WLR_EDGE_RIGHT ; 
 int WLR_MODIFIER_SHIFT ; 
 struct seatop_resize_floating_event* calloc (int,int) ; 
 int /*<<< orphan*/  container_raise_floating (struct sway_container*) ; 
 int /*<<< orphan*/  cursor_set_image (TYPE_2__*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seatop_end (struct sway_seat*) ; 
 int /*<<< orphan*/  seatop_impl ; 
 int wlr_keyboard_get_modifiers (struct wlr_keyboard*) ; 
 struct wlr_keyboard* wlr_seat_get_keyboard (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_seat_pointer_clear_focus (int /*<<< orphan*/ ) ; 
 char* wlr_xcursor_get_resize_name (int) ; 

void seatop_begin_resize_floating(struct sway_seat *seat,
		struct sway_container *con, enum wlr_edges edge) {
	seatop_end(seat);

	struct seatop_resize_floating_event *e =
		calloc(1, sizeof(struct seatop_resize_floating_event));
	if (!e) {
		return;
	}
	e->con = con;

	struct wlr_keyboard *keyboard = wlr_seat_get_keyboard(seat->wlr_seat);
	e->preserve_ratio = keyboard &&
		(wlr_keyboard_get_modifiers(keyboard) & WLR_MODIFIER_SHIFT);

	e->edge = edge == WLR_EDGE_NONE ? WLR_EDGE_BOTTOM | WLR_EDGE_RIGHT : edge;
	e->ref_lx = seat->cursor->cursor->x;
	e->ref_ly = seat->cursor->cursor->y;
	e->ref_con_lx = con->x;
	e->ref_con_ly = con->y;
	e->ref_width = con->width;
	e->ref_height = con->height;

	seat->seatop_impl = &seatop_impl;
	seat->seatop_data = e;

	container_raise_floating(con);

	const char *image = edge == WLR_EDGE_NONE ?
		"se-resize" : wlr_xcursor_get_resize_name(edge);
	cursor_set_image(seat->cursor, image, NULL);
	wlr_seat_pointer_clear_focus(seat->wlr_seat);
}