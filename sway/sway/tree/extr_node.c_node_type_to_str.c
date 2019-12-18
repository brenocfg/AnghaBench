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
typedef  enum sway_node_type { ____Placeholder_sway_node_type } sway_node_type ;

/* Variables and functions */
#define  N_CONTAINER 131 
#define  N_OUTPUT 130 
#define  N_ROOT 129 
#define  N_WORKSPACE 128 

const char *node_type_to_str(enum sway_node_type type) {
	switch (type) {
	case N_ROOT:
		return "N_ROOT";
	case N_OUTPUT:
		return "N_OUTPUT";
	case N_WORKSPACE:
		return "N_WORKSPACE";
	case N_CONTAINER:
		return "N_CONTAINER";
	}
	return "";
}