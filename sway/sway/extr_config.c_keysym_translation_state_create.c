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
struct xkb_rule_names {int dummy; } ;
struct xkb_keymap {int dummy; } ;
struct xkb_context {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  XKB_CONTEXT_NO_FLAGS ; 
 int /*<<< orphan*/  XKB_KEYMAP_COMPILE_NO_FLAGS ; 
 struct xkb_context* xkb_context_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xkb_context_unref (struct xkb_context*) ; 
 struct xkb_keymap* xkb_keymap_new_from_names (struct xkb_context*,struct xkb_rule_names*,int /*<<< orphan*/ ) ; 
 struct xkb_state* xkb_state_new (struct xkb_keymap*) ; 

__attribute__((used)) static struct xkb_state *keysym_translation_state_create(
		struct xkb_rule_names rules) {
	struct xkb_context *context = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
	struct xkb_keymap *xkb_keymap = xkb_keymap_new_from_names(
		context,
		&rules,
		XKB_KEYMAP_COMPILE_NO_FLAGS);

	xkb_context_unref(context);
	return xkb_state_new(xkb_keymap);
}