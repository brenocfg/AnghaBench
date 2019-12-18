#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wlr_xdg_popup {TYPE_4__* base; } ;
struct TYPE_10__ {int /*<<< orphan*/  notify; } ;
struct sway_layer_popup {int parent_type; TYPE_5__ new_popup; TYPE_5__ commit; TYPE_5__ destroy; TYPE_5__ unmap; TYPE_5__ map; void* parent_layer; struct wlr_xdg_popup* wlr_popup; } ;
typedef  enum layer_parent { ____Placeholder_layer_parent } layer_parent ;
struct TYPE_8__ {int /*<<< orphan*/  new_popup; int /*<<< orphan*/  destroy; int /*<<< orphan*/  unmap; int /*<<< orphan*/  map; } ;
struct TYPE_9__ {TYPE_3__ events; TYPE_2__* surface; } ;
struct TYPE_6__ {int /*<<< orphan*/  commit; } ;
struct TYPE_7__ {TYPE_1__ events; } ;

/* Variables and functions */
 struct sway_layer_popup* calloc (int,int) ; 
 int /*<<< orphan*/  popup_handle_commit ; 
 int /*<<< orphan*/  popup_handle_destroy ; 
 int /*<<< orphan*/  popup_handle_map ; 
 int /*<<< orphan*/  popup_handle_new_popup ; 
 int /*<<< orphan*/  popup_handle_unmap ; 
 int /*<<< orphan*/  popup_unconstrain (struct sway_layer_popup*) ; 
 int /*<<< orphan*/  wl_signal_add (int /*<<< orphan*/ *,TYPE_5__*) ; 

__attribute__((used)) static struct sway_layer_popup *create_popup(struct wlr_xdg_popup *wlr_popup,
		enum layer_parent parent_type, void *parent) {
	struct sway_layer_popup *popup =
		calloc(1, sizeof(struct sway_layer_popup));
	if (popup == NULL) {
		return NULL;
	}

	popup->wlr_popup = wlr_popup;
	popup->parent_type = parent_type;
	popup->parent_layer = parent;

	popup->map.notify = popup_handle_map;
	wl_signal_add(&wlr_popup->base->events.map, &popup->map);
	popup->unmap.notify = popup_handle_unmap;
	wl_signal_add(&wlr_popup->base->events.unmap, &popup->unmap);
	popup->destroy.notify = popup_handle_destroy;
	wl_signal_add(&wlr_popup->base->events.destroy, &popup->destroy);
	popup->commit.notify = popup_handle_commit;
	wl_signal_add(&wlr_popup->base->surface->events.commit, &popup->commit);
	popup->new_popup.notify = popup_handle_new_popup;
	wl_signal_add(&wlr_popup->base->events.new_popup, &popup->new_popup);

	popup_unconstrain(popup);

	return popup;
}