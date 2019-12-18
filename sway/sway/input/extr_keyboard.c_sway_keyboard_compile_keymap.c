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
struct xkb_rule_names {int /*<<< orphan*/  member_0; } ;
struct xkb_keymap {int dummy; } ;
struct xkb_context {int dummy; } ;
struct input_config {char* xkb_file; } ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/  XKB_CONTEXT_NO_FLAGS ; 
 int /*<<< orphan*/  XKB_KEYMAP_COMPILE_NO_FLAGS ; 
 int /*<<< orphan*/  XKB_KEYMAP_FORMAT_TEXT_V1 ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  fclose (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * fopen (char*,char*) ; 
 int /*<<< orphan*/  handle_xkb_context_log ; 
 int /*<<< orphan*/  input_config_fill_rule_names (struct input_config*,struct xkb_rule_names*) ; 
 char* malloc (size_t) ; 
 int snprintf (char*,size_t,char*,char*,char*) ; 
 char* strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_assert (struct xkb_context*,char*) ; 
 int /*<<< orphan*/  sway_log_errno (int /*<<< orphan*/ ,char*,char*,char*) ; 
 struct xkb_context* xkb_context_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xkb_context_set_log_fn (struct xkb_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  xkb_context_set_user_data (struct xkb_context*,char**) ; 
 int /*<<< orphan*/  xkb_context_unref (struct xkb_context*) ; 
 struct xkb_keymap* xkb_keymap_new_from_file (struct xkb_context*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct xkb_keymap* xkb_keymap_new_from_names (struct xkb_context*,struct xkb_rule_names*,int /*<<< orphan*/ ) ; 

struct xkb_keymap *sway_keyboard_compile_keymap(struct input_config *ic,
		char **error) {
	struct xkb_context *context = xkb_context_new(XKB_CONTEXT_NO_FLAGS);
	if (!sway_assert(context, "cannot create XKB context")) {
		return NULL;
	}
	xkb_context_set_user_data(context, error);
	xkb_context_set_log_fn(context, handle_xkb_context_log);

	struct xkb_keymap *keymap = NULL;

	if (ic && ic->xkb_file) {
		FILE *keymap_file = fopen(ic->xkb_file, "r");
		if (!keymap_file) {
			if (error) {
				size_t len = snprintf(NULL, 0, "cannot read XKB file %s: %s",
						ic->xkb_file, strerror(errno)) + 1;
				*error = malloc(len);
				if (*error) {
					snprintf(*error, len, "cannot read XKB file %s: %s",
							ic->xkb_file, strerror(errno));
				} else {
					sway_log_errno(SWAY_ERROR, "cannot read XKB file %s: %s",
							ic->xkb_file, strerror(errno));
				}
			} else {
				sway_log_errno(SWAY_ERROR, "cannot read XKB file %s: %s",
						ic->xkb_file, strerror(errno));
			}
			goto cleanup;
		}

		keymap = xkb_keymap_new_from_file(context, keymap_file,
					XKB_KEYMAP_FORMAT_TEXT_V1, XKB_KEYMAP_COMPILE_NO_FLAGS);

		if (!fclose(keymap_file)) {
			sway_log_errno(SWAY_ERROR, "cannot close XKB file %s: %s",
					ic->xkb_file, strerror(errno));
		}
	} else {
		struct xkb_rule_names rules = {0};
		if (ic) {
			input_config_fill_rule_names(ic, &rules);
		}
		keymap = xkb_keymap_new_from_names(context, &rules,
			XKB_KEYMAP_COMPILE_NO_FLAGS);
	}

cleanup:
	xkb_context_set_user_data(context, NULL);
	xkb_context_unref(context);
	return keymap;
}