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
struct sway_node {struct sway_container* sway_container; } ;
struct sway_container {int dummy; } ;

/* Variables and functions */
#define  L_HORIZ 132 
#define  L_NONE 131 
#define  L_STACKED 130 
#define  L_TABBED 129 
#define  L_VERT 128 
 struct sway_container* container_at_linear (struct sway_node*,double,double,struct wlr_surface**,double*,double*) ; 
 struct sway_container* container_at_stacked (struct sway_node*,double,double,struct wlr_surface**,double*,double*) ; 
 struct sway_container* container_at_tabbed (struct sway_node*,double,double,struct wlr_surface**,double*,double*) ; 
 int /*<<< orphan*/  node_get_children (struct sway_node*) ; 
 int node_get_layout (struct sway_node*) ; 
 scalar_t__ node_is_view (struct sway_node*) ; 
 int /*<<< orphan*/  surface_at_view (struct sway_container*,double,double,struct wlr_surface**,double*,double*) ; 

struct sway_container *tiling_container_at(struct sway_node *parent,
		double lx, double ly,
		struct wlr_surface **surface, double *sx, double *sy) {
	if (node_is_view(parent)) {
		surface_at_view(parent->sway_container, lx, ly, surface, sx, sy);
		return parent->sway_container;
	}
	if (!node_get_children(parent)) {
		return NULL;
	}
	switch (node_get_layout(parent)) {
	case L_HORIZ:
	case L_VERT:
		return container_at_linear(parent, lx, ly, surface, sx, sy);
	case L_TABBED:
		return container_at_tabbed(parent, lx, ly, surface, sx, sy);
	case L_STACKED:
		return container_at_stacked(parent, lx, ly, surface, sx, sy);
	case L_NONE:
		return NULL;
	}
	return NULL;
}