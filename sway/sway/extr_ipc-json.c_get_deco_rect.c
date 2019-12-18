#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct wlr_box {size_t x; size_t y; size_t width; size_t height; } ;
struct TYPE_7__ {scalar_t__ border; } ;
struct sway_container {scalar_t__ fullscreen_mode; size_t x; size_t y; size_t width; int /*<<< orphan*/  view; TYPE_5__* workspace; TYPE_3__* parent; TYPE_1__ current; } ;
typedef  enum sway_container_layout { ____Placeholder_sway_container_layout } sway_container_layout ;
struct TYPE_12__ {size_t length; } ;
struct TYPE_11__ {size_t x; size_t y; int width; TYPE_4__* tiling; } ;
struct TYPE_10__ {int length; } ;
struct TYPE_9__ {size_t x; size_t y; int width; TYPE_2__* children; } ;
struct TYPE_8__ {int length; } ;

/* Variables and functions */
 scalar_t__ B_NORMAL ; 
 scalar_t__ FULLSCREEN_NONE ; 
 int L_STACKED ; 
 int L_TABBED ; 
 TYPE_6__* container_get_siblings (struct sway_container*) ; 
 scalar_t__ container_is_floating (struct sway_container*) ; 
 int container_parent_layout (struct sway_container*) ; 
 int container_sibling_index (struct sway_container*) ; 
 size_t container_titlebar_height () ; 

__attribute__((used)) static void get_deco_rect(struct sway_container *c, struct wlr_box *deco_rect) {
	enum sway_container_layout parent_layout = container_parent_layout(c);
	bool tab_or_stack = parent_layout == L_TABBED || parent_layout == L_STACKED;
	if (((!tab_or_stack || container_is_floating(c)) &&
				c->current.border != B_NORMAL) ||
			c->fullscreen_mode != FULLSCREEN_NONE ||
			c->workspace == NULL) {
		deco_rect->x = deco_rect->y = deco_rect->width = deco_rect->height = 0;
		return;
	}

	if (c->parent) {
		deco_rect->x = c->x - c->parent->x;
		deco_rect->y = c->y - c->parent->y;
	} else {
		deco_rect->x = c->x - c->workspace->x;
		deco_rect->y = c->y - c->workspace->y;
	}
	deco_rect->width = c->width;
	deco_rect->height = container_titlebar_height();

	if (!container_is_floating(c)) {
		if (parent_layout == L_TABBED) {
			deco_rect->width = c->parent
				? c->parent->width / c->parent->children->length
				: c->workspace->width / c->workspace->tiling->length;
			deco_rect->x += deco_rect->width * container_sibling_index(c);
		} else if (parent_layout == L_STACKED) {
			if (!c->view) {
				size_t siblings = container_get_siblings(c)->length;
				deco_rect->y -= deco_rect->height * siblings;
			}
			deco_rect->y += deco_rect->height * container_sibling_index(c);
		}
	}
}