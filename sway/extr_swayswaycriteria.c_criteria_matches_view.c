#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct sway_workspace {char const* name; } ;
struct sway_view {struct sway_container* container; } ;
struct TYPE_9__ {scalar_t__ id; } ;
struct sway_container {struct sway_workspace* workspace; TYPE_2__ node; TYPE_1__* marks; } ;
struct criteria {scalar_t__ con_id; char urgent; scalar_t__ workspace; scalar_t__ tiling; scalar_t__ floating; scalar_t__ con_mark; scalar_t__ app_id; scalar_t__ shell; scalar_t__ title; scalar_t__ autofail; } ;
struct TYPE_10__ {int length; struct sway_view** items; } ;
typedef  TYPE_3__ list_t ;
struct TYPE_8__ {int length; char const** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_urgent ; 
 scalar_t__ container_is_floating (struct sway_container*) ; 
 TYPE_3__* create_list () ; 
 int /*<<< orphan*/  find_urgent_iterator ; 
 int /*<<< orphan*/  list_free (TYPE_3__*) ; 
 int /*<<< orphan*/  list_stable_sort (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ regex_cmp (char const*,scalar_t__) ; 
 int /*<<< orphan*/  root_for_each_container (int /*<<< orphan*/ ,TYPE_3__*) ; 
 char* view_get_app_id (struct sway_view*) ; 
 char* view_get_shell (struct sway_view*) ; 
 char* view_get_title (struct sway_view*) ; 
 int /*<<< orphan*/  view_is_urgent (struct sway_view*) ; 

__attribute__((used)) static bool criteria_matches_view(struct criteria *criteria,
		struct sway_view *view) {
	if (criteria->autofail) {
		return false;
	}

	if (criteria->title) {
		const char *title = view_get_title(view);
		if (!title || regex_cmp(title, criteria->title) != 0) {
			return false;
		}
	}

	if (criteria->shell) {
		const char *shell = view_get_shell(view);
		if (!shell || regex_cmp(shell, criteria->shell) != 0) {
			return false;
		}
	}

	if (criteria->app_id) {
		const char *app_id = view_get_app_id(view);
		if (!app_id || regex_cmp(app_id, criteria->app_id) != 0) {
			return false;
		}
	}

	if (criteria->con_mark) {
		bool exists = false;
		struct sway_container *con = view->container;
		for (int i = 0; i < con->marks->length; ++i) {
			if (regex_cmp(con->marks->items[i], criteria->con_mark) == 0) {
				exists = true;
				break;
			}
		}
		if (!exists) {
			return false;
		}
	}

	if (criteria->con_id) { // Internal ID
		if (!view->container || view->container->node.id != criteria->con_id) {
			return false;
		}
	}

#if HAVE_XWAYLAND
	if (criteria->id) { // X11 window ID
		uint32_t x11_window_id = view_get_x11_window_id(view);
		if (!x11_window_id || x11_window_id != criteria->id) {
			return false;
		}
	}

	if (criteria->class) {
		const char *class = view_get_class(view);
		if (!class || regex_cmp(class, criteria->class) != 0) {
			return false;
		}
	}

	if (criteria->instance) {
		const char *instance = view_get_instance(view);
		if (!instance || regex_cmp(instance, criteria->instance) != 0) {
			return false;
		}
	}

	if (criteria->window_role) {
		const char *role = view_get_window_role(view);
		if (!role || regex_cmp(role, criteria->window_role) != 0) {
			return false;
		}
	}

	if (criteria->window_type != ATOM_LAST) {
		if (!view_has_window_type(view, criteria->window_type)) {
			return false;
		}
	}
#endif

	if (criteria->floating) {
		if (!container_is_floating(view->container)) {
			return false;
		}
	}

	if (criteria->tiling) {
		if (container_is_floating(view->container)) {
			return false;
		}
	}

	if (criteria->urgent) {
		if (!view_is_urgent(view)) {
			return false;
		}
		list_t *urgent_views = create_list();
		root_for_each_container(find_urgent_iterator, urgent_views);
		list_stable_sort(urgent_views, cmp_urgent);
		struct sway_view *target;
		if (criteria->urgent == 'o') { // oldest
			target = urgent_views->items[0];
		} else { // latest
			target = urgent_views->items[urgent_views->length - 1];
		}
		list_free(urgent_views);
		if (view != target) {
			return false;
		}
	}

	if (criteria->workspace) {
		struct sway_workspace *ws = view->container->workspace;
		if (!ws || regex_cmp(ws->name, criteria->workspace) != 0) {
			return false;
		}
	}

	return true;
}