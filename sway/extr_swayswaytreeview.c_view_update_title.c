#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sway_view {TYPE_1__* container; } ;
struct TYPE_4__ {char* title; char* formatted_title; } ;

/* Variables and functions */
 char* calloc (size_t,int) ; 
 int /*<<< orphan*/  config_update_font_height (int) ; 
 int /*<<< orphan*/  container_calculate_title_height (TYPE_1__*) ; 
 int /*<<< orphan*/  container_update_title_textures (TYPE_1__*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ipc_event_window (TYPE_1__*,char*) ; 
 size_t parse_title_format (struct sway_view*,char*) ; 
 scalar_t__ strcmp (char const*,char*) ; 
 char* strdup (char const*) ; 
 int /*<<< orphan*/  sway_assert (char*,char*) ; 
 char* view_get_title (struct sway_view*) ; 

void view_update_title(struct sway_view *view, bool force) {
	const char *title = view_get_title(view);

	if (!force) {
		if (title && view->container->title &&
				strcmp(title, view->container->title) == 0) {
			return;
		}
		if (!title && !view->container->title) {
			return;
		}
	}

	free(view->container->title);
	free(view->container->formatted_title);
	if (title) {
		size_t len = parse_title_format(view, NULL);
		char *buffer = calloc(len + 1, sizeof(char));
		if (!sway_assert(buffer, "Unable to allocate title string")) {
			return;
		}
		parse_title_format(view, buffer);

		view->container->title = strdup(title);
		view->container->formatted_title = buffer;
	} else {
		view->container->title = NULL;
		view->container->formatted_title = NULL;
	}
	container_calculate_title_height(view->container);
	config_update_font_height(false);

	// Update title after the global font height is updated
	container_update_title_textures(view->container);

	ipc_event_window(view->container, "title");
}