#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct sway_output {scalar_t__ height; scalar_t__ width; } ;
typedef  enum sway_container_layout { ____Placeholder_sway_container_layout } sway_container_layout ;
struct TYPE_2__ {scalar_t__ default_layout; scalar_t__ default_orientation; } ;

/* Variables and functions */
 int L_HORIZ ; 
 scalar_t__ L_NONE ; 
 int L_VERT ; 
 TYPE_1__* config ; 

enum sway_container_layout output_get_default_layout(
		struct sway_output *output) {
	if (config->default_layout != L_NONE) {
		return config->default_layout;
	}
	if (config->default_orientation != L_NONE) {
		return config->default_orientation;
	}
	if (output->height > output->width) {
		return L_VERT;
	}
	return L_HORIZ;
}