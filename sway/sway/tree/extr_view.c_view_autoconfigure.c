#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sway_workspace {int x; int width; int y; int height; struct sway_output* output; } ;
struct sway_view {struct sway_container* container; } ;
struct sway_output {double lx; double ly; double width; double height; } ;
struct sway_container {scalar_t__ fullscreen_mode; double content_x; double content_y; double content_width; double content_height; int border_top; int border_bottom; int border_left; int border_right; int x; int width; int y; int height; int border; int border_thickness; struct sway_workspace* workspace; } ;
struct TYPE_5__ {int length; } ;
typedef  TYPE_1__ list_t ;
typedef  enum sway_container_layout { ____Placeholder_sway_container_layout } sway_container_layout ;
struct TYPE_7__ {scalar_t__ hide_edge_borders_smart; scalar_t__ hide_edge_borders; int /*<<< orphan*/  hide_lone_tab; } ;
struct TYPE_6__ {double x; double y; double width; double height; } ;

/* Variables and functions */
#define  B_CSD 131 
#define  B_NONE 130 
#define  B_NORMAL 129 
#define  B_PIXEL 128 
 scalar_t__ ESMART_NO_GAPS ; 
 scalar_t__ ESMART_ON ; 
 scalar_t__ E_BOTH ; 
 scalar_t__ E_HORIZONTAL ; 
 scalar_t__ E_VERTICAL ; 
 scalar_t__ FULLSCREEN_GLOBAL ; 
 scalar_t__ FULLSCREEN_WORKSPACE ; 
 int L_STACKED ; 
 int L_TABBED ; 
 TYPE_4__* config ; 
 TYPE_1__* container_get_siblings (struct sway_container*) ; 
 int /*<<< orphan*/  container_is_floating (struct sway_container*) ; 
 scalar_t__ container_is_scratchpad_hidden (struct sway_container*) ; 
 int container_parent_layout (struct sway_container*) ; 
 double container_titlebar_height () ; 
 int /*<<< orphan*/  gaps_to_edge (struct sway_view*) ; 
 TYPE_2__* root ; 
 scalar_t__ view_is_only_visible (struct sway_view*) ; 

void view_autoconfigure(struct sway_view *view) {
	struct sway_container *con = view->container;
	struct sway_workspace *ws = con->workspace;

	if (container_is_scratchpad_hidden(con) &&
			con->fullscreen_mode != FULLSCREEN_GLOBAL) {
		return;
	}
	struct sway_output *output = ws ? ws->output : NULL;

	if (con->fullscreen_mode == FULLSCREEN_WORKSPACE) {
		con->content_x = output->lx;
		con->content_y = output->ly;
		con->content_width = output->width;
		con->content_height = output->height;
		return;
	} else if (con->fullscreen_mode == FULLSCREEN_GLOBAL) {
		con->content_x = root->x;
		con->content_y = root->y;
		con->content_width = root->width;
		con->content_height = root->height;
		return;
	}

	con->border_top = con->border_bottom = true;
	con->border_left = con->border_right = true;
	double y_offset = 0;

	if (!container_is_floating(con) && ws) {

		bool smart = config->hide_edge_borders_smart == ESMART_ON ||
			(config->hide_edge_borders_smart == ESMART_NO_GAPS &&
			!gaps_to_edge(view));
		bool hide_smart = smart && view_is_only_visible(view);

		if (config->hide_edge_borders == E_BOTH
				|| config->hide_edge_borders == E_VERTICAL || hide_smart) {
			con->border_left = con->x != ws->x;
			int right_x = con->x + con->width;
			con->border_right = right_x != ws->x + ws->width;
		}
		if (config->hide_edge_borders == E_BOTH
				|| config->hide_edge_borders == E_HORIZONTAL || hide_smart) {
			con->border_top = con->y != ws->y;
			int bottom_y = con->y + con->height;
			con->border_bottom = bottom_y != ws->y + ws->height;
		}

		// In a tabbed or stacked container, the container's y is the top of the
		// title area. We have to offset the surface y by the height of the title,
		// bar, and disable any top border because we'll always have the title bar.
		list_t *siblings = container_get_siblings(con);
		bool show_titlebar = (siblings && siblings->length > 1)
			|| !config->hide_lone_tab;
		if (show_titlebar) {
			enum sway_container_layout layout = container_parent_layout(con);
			if (layout == L_TABBED) {
				y_offset = container_titlebar_height();
				con->border_top = false;
			} else if (layout == L_STACKED) {
				y_offset = container_titlebar_height() * siblings->length;
				con->border_top = false;
			}
		}
	}

	double x, y, width, height;
	switch (con->border) {
	default:
	case B_CSD:
	case B_NONE:
		x = con->x;
		y = con->y + y_offset;
		width = con->width;
		height = con->height - y_offset;
		break;
	case B_PIXEL:
		x = con->x + con->border_thickness * con->border_left;
		y = con->y + con->border_thickness * con->border_top + y_offset;
		width = con->width
			- con->border_thickness * con->border_left
			- con->border_thickness * con->border_right;
		height = con->height - y_offset
			- con->border_thickness * con->border_top
			- con->border_thickness * con->border_bottom;
		break;
	case B_NORMAL:
		// Height is: 1px border + 3px pad + title height + 3px pad + 1px border
		x = con->x + con->border_thickness * con->border_left;
		width = con->width
			- con->border_thickness * con->border_left
			- con->border_thickness * con->border_right;
		if (y_offset) {
			y = con->y + y_offset;
			height = con->height - y_offset
				- con->border_thickness * con->border_bottom;
		} else {
			y = con->y + container_titlebar_height();
			height = con->height - container_titlebar_height()
				- con->border_thickness * con->border_bottom;
		}
		break;
	}

	con->content_x = x;
	con->content_y = y;
	con->content_width = width;
	con->content_height = height;
}