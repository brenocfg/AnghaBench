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
struct sway_cursor {int hidden; TYPE_1__* seat; int /*<<< orphan*/  cursor; } ;
struct TYPE_2__ {int /*<<< orphan*/  wlr_seat; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlr_cursor_set_image (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wlr_seat_pointer_clear_focus (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cursor_hide(struct sway_cursor *cursor) {
	wlr_cursor_set_image(cursor->cursor, NULL, 0, 0, 0, 0, 0, 0);
	cursor->hidden = true;
	wlr_seat_pointer_clear_focus(cursor->seat->wlr_seat);
}