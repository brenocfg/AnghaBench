#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  destroy; } ;
struct wlr_subsurface {TYPE_1__ events; int /*<<< orphan*/  surface; } ;
struct sway_view_child {int /*<<< orphan*/  view; int /*<<< orphan*/  children; } ;
struct TYPE_7__ {int mapped; int /*<<< orphan*/  link; struct sway_view_child* parent; } ;
struct TYPE_6__ {int /*<<< orphan*/  notify; } ;
struct sway_subsurface {TYPE_3__ child; TYPE_2__ destroy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SWAY_ERROR ; 
 struct sway_subsurface* calloc (int,int) ; 
 int /*<<< orphan*/  subsurface_handle_destroy ; 
 int /*<<< orphan*/  subsurface_impl ; 
 int /*<<< orphan*/  sway_log (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  view_child_damage (TYPE_3__*,int) ; 
 int /*<<< orphan*/  view_child_init (TYPE_3__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl_list_insert (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wl_signal_add (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static void view_child_subsurface_create(struct sway_view_child *child,
		struct wlr_subsurface *wlr_subsurface) {
	struct sway_subsurface *subsurface =
		calloc(1, sizeof(struct sway_subsurface));
	if (subsurface == NULL) {
		sway_log(SWAY_ERROR, "Allocation failed");
		return;
	}
	subsurface->child.parent = child;
	wl_list_insert(&child->children, &subsurface->child.link);
	view_child_init(&subsurface->child, &subsurface_impl, child->view,
		wlr_subsurface->surface);

	wl_signal_add(&wlr_subsurface->events.destroy, &subsurface->destroy);
	subsurface->destroy.notify = subsurface_handle_destroy;

	subsurface->child.mapped = true;

	view_child_damage(&subsurface->child, true);
}