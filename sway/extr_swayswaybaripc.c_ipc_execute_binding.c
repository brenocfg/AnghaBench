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
typedef  int /*<<< orphan*/  uint32_t ;
struct swaybar_binding {int /*<<< orphan*/  command; int /*<<< orphan*/  release; int /*<<< orphan*/  button; } ;
struct swaybar {int /*<<< orphan*/  ipc_socketfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_COMMAND ; 
 int /*<<< orphan*/  SWAY_DEBUG ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ipc_single_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void ipc_execute_binding(struct swaybar *bar, struct swaybar_binding *bind) {
	sway_log(SWAY_DEBUG, "Executing binding for button %u (release=%d): `%s`",
			bind->button, bind->release, bind->command);
	uint32_t len = strlen(bind->command);
	free(ipc_single_command(bar->ipc_socketfd,
			IPC_COMMAND, bind->command, &len));
}