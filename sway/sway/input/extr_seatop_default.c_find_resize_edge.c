#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct wlr_surface {int dummy; } ;
struct sway_cursor {int dummy; } ;
struct sway_container {int dummy; } ;
typedef  enum wlr_edges { ____Placeholder_wlr_edges } wlr_edges ;

/* Variables and functions */
 int WLR_EDGE_NONE ; 
 int /*<<< orphan*/  container_is_floating (struct sway_container*) ; 
 scalar_t__ edge_is_external (struct sway_container*,int) ; 
 int find_edge (struct sway_container*,struct wlr_surface*,struct sway_cursor*) ; 

__attribute__((used)) static enum wlr_edges find_resize_edge(struct sway_container *cont,
		struct wlr_surface *surface, struct sway_cursor *cursor) {
	enum wlr_edges edge = find_edge(cont, surface, cursor);
	if (edge && !container_is_floating(cont) && edge_is_external(cont, edge)) {
		return WLR_EDGE_NONE;
	}
	return edge;
}