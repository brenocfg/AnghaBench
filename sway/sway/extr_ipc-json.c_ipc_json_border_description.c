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
typedef  enum sway_container_border { ____Placeholder_sway_container_border } sway_container_border ;

/* Variables and functions */
#define  B_CSD 131 
#define  B_NONE 130 
#define  B_NORMAL 129 
#define  B_PIXEL 128 

__attribute__((used)) static const char *ipc_json_border_description(enum sway_container_border border) {
	switch (border) {
	case B_NONE:
		return "none";
	case B_PIXEL:
		return "pixel";
	case B_NORMAL:
		return "normal";
	case B_CSD:
		return "csd";
	}
	return "unknown";
}