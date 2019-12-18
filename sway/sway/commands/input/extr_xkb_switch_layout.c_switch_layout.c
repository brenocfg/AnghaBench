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
typedef  scalar_t__ xkb_layout_index_t ;
struct TYPE_2__ {int /*<<< orphan*/  locked; int /*<<< orphan*/  latched; int /*<<< orphan*/  depressed; } ;
struct wlr_keyboard {TYPE_1__ modifiers; int /*<<< orphan*/  keymap; } ;

/* Variables and functions */
 int /*<<< orphan*/  wlr_keyboard_notify_modifiers (struct wlr_keyboard*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ xkb_keymap_num_layouts (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void switch_layout(struct wlr_keyboard *kbd, xkb_layout_index_t idx) {
	xkb_layout_index_t num_layouts = xkb_keymap_num_layouts(kbd->keymap);
	if (idx >= num_layouts) {
		return;
	}
	wlr_keyboard_notify_modifiers(kbd, kbd->modifiers.depressed,
		kbd->modifiers.latched, kbd->modifiers.locked, idx);
}