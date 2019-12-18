#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  error_code; int /*<<< orphan*/  atom; } ;
typedef  TYPE_1__ xcb_intern_atom_reply_t ;
typedef  int /*<<< orphan*/  xcb_intern_atom_cookie_t ;
typedef  TYPE_1__ xcb_generic_error_t ;
typedef  int /*<<< orphan*/  xcb_connection_t ;
struct wl_listener {int dummy; } ;
struct sway_xwayland {int /*<<< orphan*/ * atoms; } ;
struct sway_server {struct sway_xwayland xwayland; } ;

/* Variables and functions */
 int ATOM_LAST ; 
 int /*<<< orphan*/  SWAY_ERROR ; 
 int /*<<< orphan*/ * atom_map ; 
 int /*<<< orphan*/  free (TYPE_1__*) ; 
 struct sway_server* server ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*,int,...) ; 
 struct sway_server* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * xcb_connect (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int xcb_connection_has_error (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_disconnect (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xcb_intern_atom (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* xcb_intern_atom_reply (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__**) ; 
 int /*<<< orphan*/  xwayland_ready ; 

void handle_xwayland_ready(struct wl_listener *listener, void *data) {
	struct sway_server *server =
		wl_container_of(listener, server, xwayland_ready);
	struct sway_xwayland *xwayland = &server->xwayland;

	xcb_connection_t *xcb_conn = xcb_connect(NULL, NULL);
	int err = xcb_connection_has_error(xcb_conn);
	if (err) {
		sway_log(SWAY_ERROR, "XCB connect failed: %d", err);
		return;
	}

	xcb_intern_atom_cookie_t cookies[ATOM_LAST];
	for (size_t i = 0; i < ATOM_LAST; i++) {
		cookies[i] =
			xcb_intern_atom(xcb_conn, 0, strlen(atom_map[i]), atom_map[i]);
	}
	for (size_t i = 0; i < ATOM_LAST; i++) {
		xcb_generic_error_t *error = NULL;
		xcb_intern_atom_reply_t *reply =
			xcb_intern_atom_reply(xcb_conn, cookies[i], &error);
		if (reply != NULL && error == NULL) {
			xwayland->atoms[i] = reply->atom;
		}
		free(reply);

		if (error != NULL) {
			sway_log(SWAY_ERROR, "could not resolve atom %s, X11 error code %d",
				atom_map[i], error->error_code);
			free(error);
			break;
		}
	}

	xcb_disconnect(xcb_conn);
}