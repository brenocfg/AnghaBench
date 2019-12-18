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
struct xkb_rule_names {int /*<<< orphan*/  member_0; } ;
struct sway_mode {int /*<<< orphan*/ * keycode_bindings; int /*<<< orphan*/ * keysym_bindings; } ;
struct input_config {int /*<<< orphan*/  identifier; } ;
typedef  int /*<<< orphan*/  list_t ;
struct TYPE_4__ {TYPE_1__* modes; int /*<<< orphan*/  keysym_translation_state; } ;
struct TYPE_3__ {int length; struct sway_mode** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_DEBUG ; 
 TYPE_2__* config ; 
 int /*<<< orphan*/ * create_list () ; 
 int /*<<< orphan*/  input_config_fill_rule_names (struct input_config*,struct xkb_rule_names*) ; 
 int /*<<< orphan*/  keysym_translation_state_create (struct xkb_rule_names) ; 
 int /*<<< orphan*/  keysym_translation_state_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  translate_binding_list (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void translate_keysyms(struct input_config *input_config) {
	keysym_translation_state_destroy(config->keysym_translation_state);

	struct xkb_rule_names rules = {0};
	input_config_fill_rule_names(input_config, &rules);
	config->keysym_translation_state =
		keysym_translation_state_create(rules);

	for (int i = 0; i < config->modes->length; ++i) {
		struct sway_mode *mode = config->modes->items[i];

		list_t *bindsyms = create_list();
		list_t *bindcodes = create_list();

		translate_binding_list(mode->keysym_bindings, bindsyms, bindcodes);
		translate_binding_list(mode->keycode_bindings, bindsyms, bindcodes);

		list_free(mode->keysym_bindings);
		list_free(mode->keycode_bindings);

		mode->keysym_bindings = bindsyms;
		mode->keycode_bindings = bindcodes;
	}

	sway_log(SWAY_DEBUG, "Translated keysyms using config for device '%s'",
			input_config->identifier);
}