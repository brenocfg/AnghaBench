#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sway_view {TYPE_3__* container; } ;
struct sway_seat {int dummy; } ;
struct sway_container {TYPE_1__* workspace; struct sway_view* view; } ;
typedef  enum criteria_token { ____Placeholder_criteria_token } criteria_token ;
struct TYPE_5__ {size_t id; } ;
struct TYPE_6__ {TYPE_2__ node; } ;
struct TYPE_4__ {char* name; } ;

/* Variables and functions */
#define  T_APP_ID 137 
#define  T_CON_ID 136 
#define  T_CON_MARK 135 
#define  T_FLOATING 134 
#define  T_INVALID 133 
#define  T_SHELL 132 
#define  T_TILING 131 
#define  T_TITLE 130 
#define  T_URGENT 129 
#define  T_WORKSPACE 128 
 struct sway_seat* input_manager_current_seat () ; 
 char* malloc (size_t) ; 
 struct sway_container* seat_get_focused_container (struct sway_seat*) ; 
 int /*<<< orphan*/  snprintf (char*,size_t,char*,size_t) ; 
 char* strdup (char const*) ; 
 char* view_get_app_id (struct sway_view*) ; 
 char* view_get_shell (struct sway_view*) ; 
 char* view_get_title (struct sway_view*) ; 

__attribute__((used)) static char *get_focused_prop(enum criteria_token token, bool *autofail) {
	struct sway_seat *seat = input_manager_current_seat();
	struct sway_container *focus = seat_get_focused_container(seat);

	struct sway_view *view = focus ? focus->view : NULL;
	const char *value = NULL;

	switch (token) {
	case T_APP_ID:
		*autofail = true;
		if (view) {
			value = view_get_app_id(view);
		}
		break;
	case T_SHELL:
		*autofail = true;
		if (view) {
			value = view_get_shell(view);
		}
		break;
	case T_TITLE:
		*autofail = true;
		if (view) {
			value = view_get_title(view);
		}
		break;
	case T_WORKSPACE:
		*autofail = true;
		if (focus && focus->workspace) {
			value = focus->workspace->name;
		}
		break;
	case T_CON_ID:
		*autofail = true;
		if (view && view->container) {
			size_t id = view->container->node.id;
			size_t id_size = snprintf(NULL, 0, "%zu", id) + 1;
			char *id_str = malloc(id_size);
			snprintf(id_str, id_size, "%zu", id);
			value = id_str;
		}
		break;
#if HAVE_XWAYLAND
	case T_CLASS:
		*autofail = true;
		if (view) {
			value = view_get_class(view);
		}
		break;
	case T_INSTANCE:
		*autofail = true;
		if (view) {
			value = view_get_instance(view);
		}
		break;
	case T_WINDOW_ROLE:
		*autofail = true;
		if (view) {
			value = view_get_window_role(view);
		}
		break;
	case T_WINDOW_TYPE: // These do not support __focused__
	case T_ID:
#endif
	case T_CON_MARK:
	case T_FLOATING:
	case T_TILING:
	case T_URGENT:
	case T_INVALID:
		*autofail = false;
		break;
	}
	if (value) {
		return strdup(value);
	}
	return NULL;
}