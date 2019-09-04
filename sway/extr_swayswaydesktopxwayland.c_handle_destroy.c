#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_15__ ;
typedef  struct TYPE_20__   TYPE_14__ ;
typedef  struct TYPE_19__   TYPE_13__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
struct wl_listener {int dummy; } ;
struct sway_view {scalar_t__ surface; } ;
struct TYPE_21__ {int /*<<< orphan*/  link; } ;
struct TYPE_20__ {int /*<<< orphan*/  link; } ;
struct TYPE_19__ {int /*<<< orphan*/  link; } ;
struct TYPE_18__ {int /*<<< orphan*/  link; } ;
struct TYPE_17__ {int /*<<< orphan*/  link; } ;
struct TYPE_16__ {int /*<<< orphan*/  link; } ;
struct TYPE_30__ {int /*<<< orphan*/  link; } ;
struct TYPE_29__ {int /*<<< orphan*/  link; } ;
struct TYPE_28__ {int /*<<< orphan*/  link; } ;
struct TYPE_27__ {int /*<<< orphan*/  link; } ;
struct TYPE_26__ {int /*<<< orphan*/  link; } ;
struct TYPE_25__ {int /*<<< orphan*/  link; } ;
struct TYPE_24__ {int /*<<< orphan*/  link; } ;
struct TYPE_23__ {int /*<<< orphan*/  link; } ;
struct TYPE_22__ {int /*<<< orphan*/  link; } ;
struct sway_xwayland_view {struct sway_view view; TYPE_15__ unmap; TYPE_14__ map; TYPE_13__ set_decorations; TYPE_12__ set_hints; TYPE_11__ set_window_type; TYPE_10__ set_role; TYPE_9__ set_class; TYPE_8__ set_title; TYPE_7__ request_activate; TYPE_6__ request_resize; TYPE_5__ request_move; TYPE_4__ request_fullscreen; TYPE_3__ request_configure; TYPE_2__ destroy; TYPE_1__ commit; } ;

/* Variables and functions */
 int /*<<< orphan*/  destroy ; 
 int /*<<< orphan*/  view_begin_destroy (struct sway_view*) ; 
 int /*<<< orphan*/  view_unmap (struct sway_view*) ; 
 struct sway_xwayland_view* wl_container_of (struct wl_listener*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_remove (int /*<<< orphan*/ *) ; 
 struct sway_xwayland_view* xwayland_view ; 

__attribute__((used)) static void handle_destroy(struct wl_listener *listener, void *data) {
	struct sway_xwayland_view *xwayland_view =
		wl_container_of(listener, xwayland_view, destroy);
	struct sway_view *view = &xwayland_view->view;

	if (view->surface) {
		view_unmap(view);
		wl_list_remove(&xwayland_view->commit.link);
	}

	wl_list_remove(&xwayland_view->destroy.link);
	wl_list_remove(&xwayland_view->request_configure.link);
	wl_list_remove(&xwayland_view->request_fullscreen.link);
	wl_list_remove(&xwayland_view->request_move.link);
	wl_list_remove(&xwayland_view->request_resize.link);
	wl_list_remove(&xwayland_view->request_activate.link);
	wl_list_remove(&xwayland_view->set_title.link);
	wl_list_remove(&xwayland_view->set_class.link);
	wl_list_remove(&xwayland_view->set_role.link);
	wl_list_remove(&xwayland_view->set_window_type.link);
	wl_list_remove(&xwayland_view->set_hints.link);
	wl_list_remove(&xwayland_view->set_decorations.link);
	wl_list_remove(&xwayland_view->map.link);
	wl_list_remove(&xwayland_view->unmap.link);
	view_begin_destroy(&xwayland_view->view);
}