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
typedef  enum sway_container_layout { ____Placeholder_sway_container_layout } sway_container_layout ;

/* Variables and functions */
#define  L_HORIZ 132 
#define  L_NONE 131 
#define  L_STACKED 130 
#define  L_TABBED 129 
#define  L_VERT 128 

__attribute__((used)) static const char *ipc_json_layout_description(enum sway_container_layout l) {
	switch (l) {
	case L_VERT:
		return "splitv";
	case L_HORIZ:
		return "splith";
	case L_TABBED:
		return "tabbed";
	case L_STACKED:
		return "stacked";
	case L_NONE:
		break;
	}
	return "none";
}