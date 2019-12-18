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
struct TYPE_8__ {int x; int y; } ;
struct wlr_xdg_popup {TYPE_3__ geometry; TYPE_2__* base; } ;
struct wlr_surface {int dummy; } ;
struct wlr_output {struct sway_output* data; } ;
struct sway_output {int dummy; } ;
struct TYPE_9__ {scalar_t__ y; scalar_t__ x; } ;
struct sway_layer_surface {TYPE_5__* layer_surface; TYPE_4__ geo; } ;
struct sway_layer_popup {scalar_t__ parent_type; struct sway_layer_surface* parent_layer; struct wlr_xdg_popup* wlr_popup; struct sway_layer_popup* parent_popup; } ;
struct TYPE_10__ {struct wlr_output* output; } ;
struct TYPE_6__ {int x; int y; } ;
struct TYPE_7__ {TYPE_1__ geometry; struct wlr_surface* surface; } ;

/* Variables and functions */
 scalar_t__ LAYER_PARENT_POPUP ; 
 int /*<<< orphan*/  output_damage_surface (struct sway_output*,int,int,struct wlr_surface*,int) ; 

__attribute__((used)) static void popup_damage(struct sway_layer_popup *layer_popup, bool whole) {
	struct wlr_xdg_popup *popup = layer_popup->wlr_popup;
	struct wlr_surface *surface = popup->base->surface;
	int popup_sx = popup->geometry.x - popup->base->geometry.x;
	int popup_sy = popup->geometry.y - popup->base->geometry.y;
	int ox = popup_sx, oy = popup_sy;
	struct sway_layer_surface *layer;
	while (true) {
		if (layer_popup->parent_type == LAYER_PARENT_POPUP) {
			layer_popup = layer_popup->parent_popup;
			ox += layer_popup->wlr_popup->geometry.x;
			oy += layer_popup->wlr_popup->geometry.y;
		} else {
			layer = layer_popup->parent_layer;
			ox += layer->geo.x;
			oy += layer->geo.y;
			break;
		}
	}
	struct wlr_output *wlr_output = layer->layer_surface->output;
	struct sway_output *output = wlr_output->data;
	output_damage_surface(output, ox, oy, surface, whole);
}