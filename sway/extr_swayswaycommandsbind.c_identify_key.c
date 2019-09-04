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
typedef  scalar_t__ xkb_keysym_t ;
typedef  scalar_t__ xkb_keycode_t ;
typedef  scalar_t__ uint32_t ;
struct cmd_results {int dummy; } ;
typedef  enum binding_input_type { ____Placeholder_binding_input_type } binding_input_type ;

/* Variables and functions */
 int BINDING_KEYCODE ; 
 int BINDING_MOUSECODE ; 
 int BINDING_MOUSESYM ; 
 int /*<<< orphan*/  CMD_INVALID ; 
 int /*<<< orphan*/  XKB_KEYSYM_CASE_INSENSITIVE ; 
 struct cmd_results* cmd_results_new (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ get_mouse_bindcode (char const*,char**) ; 
 scalar_t__ get_mouse_bindsym (char const*,char**) ; 
 scalar_t__ strtol (char const*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  xkb_keycode_is_legal_ext (scalar_t__) ; 
 scalar_t__ xkb_keysym_from_name (char const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct cmd_results *identify_key(const char* name, bool first_key,
		uint32_t* key_val, enum binding_input_type* type) {
	if (*type == BINDING_MOUSECODE) {
		// check for mouse bindcodes
		char *message = NULL;
		uint32_t button = get_mouse_bindcode(name, &message);
		if (!button) {
			if (message) {
				struct cmd_results *error =
					cmd_results_new(CMD_INVALID, message);
				free(message);
				return error;
			} else {
				return cmd_results_new(CMD_INVALID,
						"Unknown button code %s", name);
			}
		}
		*key_val = button;
	} else if (*type == BINDING_MOUSESYM) {
		// check for mouse bindsyms (x11 buttons or event names)
		char *message = NULL;
		uint32_t button = get_mouse_bindsym(name, &message);
		if (!button) {
			if (message) {
				struct cmd_results *error =
					cmd_results_new(CMD_INVALID, message);
				free(message);
				return error;
			} else if (!button) {
				return cmd_results_new(CMD_INVALID, "Unknown button %s", name);
			}
		}
		*key_val = button;
	} else if (*type == BINDING_KEYCODE) {
		// check for keycode. If it is the first key, allow mouse bindcodes
		if (first_key) {
			char *message = NULL;
			uint32_t button = get_mouse_bindcode(name, &message);
			free(message);
			if (button) {
				*type = BINDING_MOUSECODE;
				*key_val = button;
				return NULL;
			}
		}

		xkb_keycode_t keycode = strtol(name, NULL, 10);
		if (!xkb_keycode_is_legal_ext(keycode)) {
			if (first_key) {
				return cmd_results_new(CMD_INVALID,
						"Invalid keycode or button code '%s'", name);
			} else {
				return cmd_results_new(CMD_INVALID,
						"Invalid keycode '%s'", name);
			}
		}
		*key_val = keycode;
	} else {
		// check for keysym. If it is the first key, allow mouse bindsyms
		if (first_key) {
			char *message = NULL;
			uint32_t button = get_mouse_bindsym(name, &message);
			if (message) {
				struct cmd_results *error =
					cmd_results_new(CMD_INVALID, message);
				free(message);
				return error;
			} else if (button) {
				*type = BINDING_MOUSESYM;
				*key_val = button;
				return NULL;
			}
		}

		xkb_keysym_t keysym = xkb_keysym_from_name(name,
				XKB_KEYSYM_CASE_INSENSITIVE);
		if (!keysym) {
			if (first_key) {
				return cmd_results_new(CMD_INVALID,
						"Unknown key or button '%s'", name);
			} else {
				return cmd_results_new(CMD_INVALID, "Unknown key '%s'", name);
			}
		}
		*key_val = keysym;
	}
	return NULL;
}