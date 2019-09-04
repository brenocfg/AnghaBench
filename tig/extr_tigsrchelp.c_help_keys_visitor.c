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
struct view {struct help_state* private; } ;
struct run_request {int dummy; } ;
struct request_info {int /*<<< orphan*/  name; } ;
struct keymap {scalar_t__ hidden; } ;
struct help_state {void* name_width; void* keys_width; } ;
struct help_request_iterator {struct view* view; struct keymap* keymap; } ;
struct TYPE_2__ {char const* text; struct request_info const* req_info; } ;
struct help {int request; TYPE_1__ data; } ;
typedef  enum request { ____Placeholder_request } request ;

/* Variables and functions */
 int /*<<< orphan*/  LINE_DEFAULT ; 
 int /*<<< orphan*/  LINE_HELP_GROUP ; 
 int /*<<< orphan*/  LINE_SECTION ; 
 void* MAX (void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  add_help_line (struct view*,struct help**,struct keymap*,int /*<<< orphan*/ ) ; 
 char const* enum_name (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strlen (char const*) ; 

__attribute__((used)) static bool
help_keys_visitor(void *data, const char *group, struct keymap *keymap,
		  enum request request, const char *key,
		  const struct request_info *req_info, const struct run_request *run_req)
{
	struct help_request_iterator *iterator = data;
	struct view *view = iterator->view;
	struct help_state *state = view->private;
	struct help *help;

	if (iterator->keymap != keymap) {
		iterator->keymap = keymap;
		if (!add_help_line(iterator->view, &help, keymap, LINE_SECTION))
			return false;
	}

	if (keymap->hidden)
		return true;

	if (group) {
		if (!add_help_line(iterator->view, &help, keymap, LINE_HELP_GROUP))
			return false;
		help->data.text = group;
	}

	if (!add_help_line(view, &help, keymap, LINE_DEFAULT))
		return false;

	state->keys_width = MAX(state->keys_width, strlen(key));
	help->request = request;

	if (req_info) {
		state->name_width = MAX(state->name_width, strlen(enum_name(req_info->name)));
		help->data.req_info = req_info;
	}

	return true;
}