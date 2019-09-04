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
typedef  int /*<<< orphan*/  uint32_t ;
struct ipc_client {int subscribed_events; } ;
typedef  enum ipc_command_type { ____Placeholder_ipc_command_type } ipc_command_type ;
struct TYPE_2__ {int length; struct ipc_client** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_INFO ; 
 int event_mask (int) ; 
 TYPE_1__* ipc_client_list ; 
 int /*<<< orphan*/  ipc_send_reply (struct ipc_client*,int,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ strlen (char const*) ; 
 int /*<<< orphan*/  sway_log_errno (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void ipc_send_event(const char *json_string, enum ipc_command_type event) {
	struct ipc_client *client;
	for (int i = 0; i < ipc_client_list->length; i++) {
		client = ipc_client_list->items[i];
		if ((client->subscribed_events & event_mask(event)) == 0) {
			continue;
		}
		if (!ipc_send_reply(client, event, json_string,
				(uint32_t)strlen(json_string))) {
			sway_log_errno(SWAY_INFO, "Unable to send reply to IPC client");
			/* ipc_send_reply destroys client on error, which also
			 * removes it from the list, so we need to process
			 * current index again */
			i--;
		}
	}
}