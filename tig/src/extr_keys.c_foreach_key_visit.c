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
struct run_request {int dummy; } ;
struct request_info {int dummy; } ;
struct keymap {int size; struct keybinding** data; } ;
struct keybinding {int request; int /*<<< orphan*/  keys; int /*<<< orphan*/  key; } ;
struct key_visitor_state {char const* group; int (* visitor ) (int /*<<< orphan*/ ,char const*,struct keymap*,int,char const*,struct request_info const*,struct run_request const*) ;int /*<<< orphan*/  data; scalar_t__ combine_keys; struct keymap* keymap; } ;
typedef  enum request { ____Placeholder_request } request ;

/* Variables and functions */
 char* get_key_name (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 char* get_keys (struct keymap*,int,int) ; 
 int stub1 (int /*<<< orphan*/ ,char const*,struct keymap*,int,char const*,struct request_info const*,struct run_request const*) ; 
 int stub2 (int /*<<< orphan*/ ,char const*,struct keymap*,int,char const*,struct request_info const*,struct run_request const*) ; 

__attribute__((used)) static bool
foreach_key_visit(struct key_visitor_state *state, const char *group,
		  enum request request,
		  const struct request_info *req_info, const struct run_request *run_req)
{
	struct keymap *keymap = state->keymap;
	int i;

	if (state->group == group)
		group = NULL;

	if (state->combine_keys) {
		const char *key = get_keys(keymap, request, true);

		if (!key || !*key)
			return true;

		if (group)
			state->group = group;
		return state->visitor(state->data, group, keymap, request,
				      key, req_info, run_req);
	}

	for (i = 0; i < keymap->size; i++) {
		if (keymap->data[i]->request == request) {
			struct keybinding *keybinding = keymap->data[i];
			const char *key = get_key_name(keybinding->key, keybinding->keys, false);

			if (!key || !*key)
				continue;

			if (!state->visitor(state->data, group, keymap, request,
					    key, req_info, run_req))
				return false;

			if (group)
				state->group = group;
			group = NULL;
		}
	}

	return true;
}