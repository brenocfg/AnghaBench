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
struct TYPE_2__ {int length; int /*<<< orphan*/ * items; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_event_window (struct sway_container*,char*) ; 

void container_clear_marks(struct sway_container *con) {
	for (int i = 0; i < con->marks->length; ++i) {
		free(con->marks->items[i]);
	}
	con->marks->length = 0;
	ipc_event_window(con, "mark");
}