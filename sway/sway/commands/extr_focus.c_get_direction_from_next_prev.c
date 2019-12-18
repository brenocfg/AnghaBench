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
struct sway_seat {int dummy; } ;
struct sway_container {int dummy; } ;
typedef  enum wlr_direction { ____Placeholder_wlr_direction } wlr_direction ;
typedef  enum sway_container_layout { ____Placeholder_sway_container_layout } sway_container_layout ;

/* Variables and functions */
#define  L_HORIZ 132 
#define  L_NONE 131 
#define  L_STACKED 130 
#define  L_TABBED 129 
#define  L_VERT 128 
 int WLR_DIRECTION_DOWN ; 
 int WLR_DIRECTION_LEFT ; 
 int WLR_DIRECTION_RIGHT ; 
 int WLR_DIRECTION_UP ; 
 int container_parent_layout (struct sway_container*) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static bool get_direction_from_next_prev(struct sway_container *container,
		struct sway_seat *seat, const char *name, enum wlr_direction *out) {
	enum sway_container_layout parent_layout = L_NONE;
	if (container) {
		parent_layout = container_parent_layout(container);
	}

	if (strcasecmp(name, "prev") == 0) {
		switch (parent_layout) {
		case L_HORIZ:
		case L_TABBED:
			*out = WLR_DIRECTION_LEFT;
			break;
		case L_VERT:
		case L_STACKED:
			*out = WLR_DIRECTION_UP;
			break;
		case L_NONE:
			return true;
		default:
			return false;
		}
	} else if (strcasecmp(name, "next") == 0) {
		switch (parent_layout) {
		case L_HORIZ:
		case L_TABBED:
			*out = WLR_DIRECTION_RIGHT;
			break;
		case L_VERT:
		case L_STACKED:
			*out = WLR_DIRECTION_DOWN;
			break;
		case L_NONE:
			return true;
		default:
			return false;
		}
	} else {
		return false;
	}
	 
	return true;
}