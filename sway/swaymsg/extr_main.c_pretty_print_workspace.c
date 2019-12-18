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
typedef  int /*<<< orphan*/  json_object ;

/* Variables and functions */
 scalar_t__ json_object_get_boolean (int /*<<< orphan*/ *) ; 
 char* json_object_get_string (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  json_object_object_get_ex (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  printf (char*,char*,char*,char*,char*,char*,char*,char*) ; 

__attribute__((used)) static void pretty_print_workspace(json_object *w) {
	json_object *name, *rect, *visible, *output, *urgent, *layout,
				*representation, *focused;
	json_object_object_get_ex(w, "name", &name);
	json_object_object_get_ex(w, "rect", &rect);
	json_object_object_get_ex(w, "visible", &visible);
	json_object_object_get_ex(w, "output", &output);
	json_object_object_get_ex(w, "urgent", &urgent);
	json_object_object_get_ex(w, "layout", &layout);
	json_object_object_get_ex(w, "representation", &representation);
	json_object_object_get_ex(w, "focused", &focused);
	printf(
		"Workspace %s%s%s%s\n"
		"  Output: %s\n"
		"  Layout: %s\n"
		"  Representation: %s\n\n",
		json_object_get_string(name),
		json_object_get_boolean(focused) ? " (focused)" : "",
		!json_object_get_boolean(visible) ? " (off-screen)" : "",
		json_object_get_boolean(urgent) ? " (urgent)" : "",
		json_object_get_string(output),
		json_object_get_string(layout),
		json_object_get_string(representation)
	);
}