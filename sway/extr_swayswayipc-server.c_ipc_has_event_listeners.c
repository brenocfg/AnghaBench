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
struct ipc_client {int subscribed_events; } ;
typedef  enum ipc_command_type { ____Placeholder_ipc_command_type } ipc_command_type ;
struct TYPE_2__ {int length; struct ipc_client** items; } ;

/* Variables and functions */
 int event_mask (int) ; 
 TYPE_1__* ipc_client_list ; 

__attribute__((used)) static bool ipc_has_event_listeners(enum ipc_command_type event) {
	for (int i = 0; i < ipc_client_list->length; i++) {
		struct ipc_client *client = ipc_client_list->items[i];
		if ((client->subscribed_events & event_mask(event)) != 0) {
			return true;
		}
	}
	return false;
}