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
typedef  enum wlr_direction { ____Placeholder_wlr_direction } wlr_direction ;
typedef  enum sway_container_layout { ____Placeholder_sway_container_layout } sway_container_layout ;

/* Variables and functions */
#define  L_HORIZ 131 
#define  L_STACKED 130 
#define  L_TABBED 129 
#define  L_VERT 128 
 int WLR_DIRECTION_DOWN ; 
 int WLR_DIRECTION_LEFT ; 
 int WLR_DIRECTION_RIGHT ; 
 int WLR_DIRECTION_UP ; 

__attribute__((used)) static bool is_parallel(enum sway_container_layout layout,
		enum wlr_direction dir) {
	switch (layout) {
	case L_TABBED:
	case L_HORIZ:
		return dir == WLR_DIRECTION_LEFT || dir == WLR_DIRECTION_RIGHT;
	case L_STACKED:
	case L_VERT:
		return dir == WLR_DIRECTION_UP || dir == WLR_DIRECTION_DOWN;
	default:
		return false;
	}
}