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
struct wl_listener {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  link; } ;
struct TYPE_3__ {int /*<<< orphan*/  link; } ;
struct sway_tablet_tool {TYPE_2__ set_cursor; TYPE_1__ tool_destroy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct sway_tablet_tool*) ; 
 struct sway_tablet_tool* tool ; 
 int /*<<< orphan*/  tool_destroy ; 
 struct sway_tablet_tool* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_tablet_tool_destroy(struct wl_listener *listener, void *data) {
	struct sway_tablet_tool *tool =
		wl_container_of(listener, tool, tool_destroy);

	wl_list_remove(&tool->tool_destroy.link);
	wl_list_remove(&tool->set_cursor.link);

	free(tool);
}