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
struct sway_mode {TYPE_1__* switch_bindings; TYPE_1__* mouse_bindings; TYPE_1__* keycode_bindings; TYPE_1__* keysym_bindings; struct sway_mode* name; } ;
struct TYPE_2__ {int length; int /*<<< orphan*/ * items; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sway_mode*) ; 
 int /*<<< orphan*/  free_sway_binding (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free_switch_binding (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_free (TYPE_1__*) ; 

__attribute__((used)) static void free_mode(struct sway_mode *mode) {
	if (!mode) {
		return;
	}
	free(mode->name);
	if (mode->keysym_bindings) {
		for (int i = 0; i < mode->keysym_bindings->length; i++) {
			free_sway_binding(mode->keysym_bindings->items[i]);
		}
		list_free(mode->keysym_bindings);
	}
	if (mode->keycode_bindings) {
		for (int i = 0; i < mode->keycode_bindings->length; i++) {
			free_sway_binding(mode->keycode_bindings->items[i]);
		}
		list_free(mode->keycode_bindings);
	}
	if (mode->mouse_bindings) {
		for (int i = 0; i < mode->mouse_bindings->length; i++) {
			free_sway_binding(mode->mouse_bindings->items[i]);
		}
		list_free(mode->mouse_bindings);
	}
	if (mode->switch_bindings) {
		for (int i = 0; i < mode->switch_bindings->length; i++) {
			free_switch_binding(mode->switch_bindings->items[i]);
		}
		list_free(mode->switch_bindings);
	}
	free(mode);
}