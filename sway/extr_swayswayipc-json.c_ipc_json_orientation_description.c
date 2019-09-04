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
#define  L_HORIZ 129 
#define  L_VERT 128 

__attribute__((used)) static const char *ipc_json_orientation_description(enum sway_container_layout l) {
	switch (l) {
	case L_VERT:
		return "vertical";
	case L_HORIZ:
		return "horizontal";
	default:
		return "none";
	}
}