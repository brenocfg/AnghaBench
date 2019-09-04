#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;
typedef  struct TYPE_12__   TYPE_10__ ;

/* Type definitions */
struct TYPE_18__ {int /*<<< orphan*/  new_popup; } ;
struct TYPE_13__ {scalar_t__ height; scalar_t__ width; } ;
struct wlr_xdg_surface {TYPE_8__* toplevel; TYPE_6__ events; TYPE_10__* surface; TYPE_1__ geometry; } ;
struct wl_listener {int dummy; } ;
struct TYPE_21__ {int /*<<< orphan*/  notify; } ;
struct sway_view {struct wlr_xdg_surface* wlr_xdg_surface; int /*<<< orphan*/  xdg_decoration; scalar_t__ natural_height; scalar_t__ natural_width; } ;
struct sway_xdg_shell_view {TYPE_9__ set_app_id; TYPE_9__ set_title; TYPE_9__ request_resize; TYPE_9__ request_move; TYPE_9__ request_fullscreen; TYPE_9__ new_popup; TYPE_9__ commit; struct sway_view view; } ;
struct sway_server_decoration {TYPE_3__* wlr_server_decoration; } ;
struct TYPE_19__ {int /*<<< orphan*/  set_app_id; int /*<<< orphan*/  set_title; int /*<<< orphan*/  request_resize; int /*<<< orphan*/  request_move; int /*<<< orphan*/  request_fullscreen; } ;
struct TYPE_16__ {int /*<<< orphan*/  fullscreen_output; int /*<<< orphan*/  fullscreen; } ;
struct TYPE_20__ {TYPE_7__ events; TYPE_4__ client_pending; } ;
struct TYPE_17__ {int /*<<< orphan*/  commit; } ;
struct TYPE_15__ {scalar_t__ mode; } ;
struct TYPE_14__ {scalar_t__ height; scalar_t__ width; } ;
struct TYPE_12__ {TYPE_5__ events; TYPE_2__ current; } ;

/* Variables and functions */
 scalar_t__ WLR_SERVER_DECORATION_MANAGER_MODE_CLIENT ; 
 struct sway_server_decoration* decoration_from_surface (TYPE_10__*) ; 
 int /*<<< orphan*/  handle_commit ; 
 int /*<<< orphan*/  handle_new_popup ; 
 int /*<<< orphan*/  handle_request_fullscreen ; 
 int /*<<< orphan*/  handle_request_move ; 
 int /*<<< orphan*/  handle_request_resize ; 
 int /*<<< orphan*/  handle_set_app_id ; 
 int /*<<< orphan*/  handle_set_title ; 
 int /*<<< orphan*/  map ; 
 int /*<<< orphan*/  transaction_commit_dirty () ; 
 int /*<<< orphan*/  view_map (struct sway_view*,TYPE_10__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct sway_xdg_shell_view* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_signal_add (int /*<<< orphan*/ *,TYPE_9__*) ; 
 struct sway_xdg_shell_view* xdg_shell_view ; 

__attribute__((used)) static void handle_map(struct wl_listener *listener, void *data) {
	struct sway_xdg_shell_view *xdg_shell_view =
		wl_container_of(listener, xdg_shell_view, map);
	struct sway_view *view = &xdg_shell_view->view;
	struct wlr_xdg_surface *xdg_surface = view->wlr_xdg_surface;

	view->natural_width = view->wlr_xdg_surface->geometry.width;
	view->natural_height = view->wlr_xdg_surface->geometry.height;
	if (!view->natural_width && !view->natural_height) {
		view->natural_width = view->wlr_xdg_surface->surface->current.width;
		view->natural_height = view->wlr_xdg_surface->surface->current.height;
	}

	bool csd = false;

	if (!view->xdg_decoration) {
		struct sway_server_decoration *deco =
				decoration_from_surface(xdg_surface->surface);
		csd = !deco || deco->wlr_server_decoration->mode ==
			WLR_SERVER_DECORATION_MANAGER_MODE_CLIENT;

	}

	view_map(view, view->wlr_xdg_surface->surface,
		xdg_surface->toplevel->client_pending.fullscreen,
		xdg_surface->toplevel->client_pending.fullscreen_output,
		csd);

	transaction_commit_dirty();

	xdg_shell_view->commit.notify = handle_commit;
	wl_signal_add(&xdg_surface->surface->events.commit,
		&xdg_shell_view->commit);

	xdg_shell_view->new_popup.notify = handle_new_popup;
	wl_signal_add(&xdg_surface->events.new_popup,
		&xdg_shell_view->new_popup);

	xdg_shell_view->request_fullscreen.notify = handle_request_fullscreen;
	wl_signal_add(&xdg_surface->toplevel->events.request_fullscreen,
			&xdg_shell_view->request_fullscreen);

	xdg_shell_view->request_move.notify = handle_request_move;
	wl_signal_add(&xdg_surface->toplevel->events.request_move,
			&xdg_shell_view->request_move);

	xdg_shell_view->request_resize.notify = handle_request_resize;
	wl_signal_add(&xdg_surface->toplevel->events.request_resize,
			&xdg_shell_view->request_resize);

	xdg_shell_view->set_title.notify = handle_set_title;
	wl_signal_add(&xdg_surface->toplevel->events.set_title,
			&xdg_shell_view->set_title);

	xdg_shell_view->set_app_id.notify = handle_set_app_id;
	wl_signal_add(&xdg_surface->toplevel->events.set_app_id,
			&xdg_shell_view->set_app_id);
}