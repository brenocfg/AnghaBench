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
struct sway_container {TYPE_1__* marks; } ;
struct TYPE_2__ {int length; char** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  container_update_marks_textures (struct sway_container*) ; 
 int /*<<< orphan*/  find_by_mark_iterator ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ipc_event_window (struct sway_container*,char*) ; 
 int /*<<< orphan*/  list_del (TYPE_1__*,int) ; 
 struct sway_container* root_find_container (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 

bool container_find_and_unmark(char *mark) {
	struct sway_container *con = root_find_container(
		find_by_mark_iterator, mark);
	if (!con) {
		return false;
	}

	for (int i = 0; i < con->marks->length; ++i) {
		char *con_mark = con->marks->items[i];
		if (strcmp(con_mark, mark) == 0) {
			free(con_mark);
			list_del(con->marks, i);
			container_update_marks_textures(con);
			ipc_event_window(con, "mark");
			return true;
		}
	}
	return false;
}