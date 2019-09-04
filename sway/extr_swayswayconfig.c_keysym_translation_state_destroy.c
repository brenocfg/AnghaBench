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
struct xkb_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  xkb_keymap_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xkb_state_get_keymap (struct xkb_state*) ; 
 int /*<<< orphan*/  xkb_state_unref (struct xkb_state*) ; 

__attribute__((used)) static void keysym_translation_state_destroy(
		struct xkb_state *state) {
	xkb_keymap_unref(xkb_state_get_keymap(state));
	xkb_state_unref(state);
}