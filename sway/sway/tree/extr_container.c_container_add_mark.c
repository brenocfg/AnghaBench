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
struct sway_container {int /*<<< orphan*/  marks; } ;

/* Variables and functions */
 int /*<<< orphan*/  ipc_event_window (struct sway_container*,char*) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strdup (char*) ; 

void container_add_mark(struct sway_container *con, char *mark) {
	list_add(con->marks, strdup(mark));
	ipc_event_window(con, "mark");
}