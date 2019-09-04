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
typedef  int uint32_t ;
struct swaybar {int /*<<< orphan*/  ipc_socketfd; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPC_COMMAND ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  ipc_single_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 char* malloc (int) ; 
 int /*<<< orphan*/  strcpy (char*,char*) ; 
 size_t strlen (char const*) ; 

void ipc_send_workspace_command(struct swaybar *bar, const char *ws) {
	uint32_t size = strlen("workspace \"\"") + strlen(ws);
	for (size_t i = 0; i < strlen(ws); ++i) {
		if (ws[i] == '"' || ws[i] == '\\') {
			++size;
		}
	}

	char *command = malloc(size + 1);
	if (!command) {
		return;
	}

	strcpy(command, "workspace \"");
	strcpy(&command[size - 1], "\"");
	for (size_t i = 0, d = strlen("workspace \""); i < strlen(ws); ++i) {
		if (ws[i] == '"' || ws[i] == '\\') {
			command[d++] = '\\';
		}
		command[d++] = ws[i];
	}

	ipc_single_command(bar->ipc_socketfd, IPC_COMMAND, command, &size);
	free(command);
}