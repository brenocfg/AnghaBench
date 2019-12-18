#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wl_listener {int dummy; } ;
struct TYPE_8__ {int /*<<< orphan*/  link; } ;
struct TYPE_7__ {int /*<<< orphan*/  sun_path; } ;
struct TYPE_6__ {int length; int /*<<< orphan*/ * items; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  ipc_client_disconnect (int /*<<< orphan*/ ) ; 
 TYPE_1__* ipc_client_list ; 
 TYPE_3__ ipc_display_destroy ; 
 scalar_t__ ipc_event_source ; 
 TYPE_2__* ipc_sockaddr ; 
 int /*<<< orphan*/  ipc_socket ; 
 int /*<<< orphan*/  list_free (TYPE_1__*) ; 
 int /*<<< orphan*/  unlink (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_event_source_remove (scalar_t__) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void handle_display_destroy(struct wl_listener *listener, void *data) {
	if (ipc_event_source) {
		wl_event_source_remove(ipc_event_source);
	}
	close(ipc_socket);
	unlink(ipc_sockaddr->sun_path);

	while (ipc_client_list->length) {
		ipc_client_disconnect(ipc_client_list->items[ipc_client_list->length-1]);
	}
	list_free(ipc_client_list);

	free(ipc_sockaddr);

	wl_list_remove(&ipc_display_destroy.link);
}