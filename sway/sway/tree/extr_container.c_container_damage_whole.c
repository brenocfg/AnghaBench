#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sway_output {int dummy; } ;
struct sway_container {int dummy; } ;
struct TYPE_4__ {TYPE_1__* outputs; } ;
struct TYPE_3__ {int length; struct sway_output** items; } ;

/* Variables and functions */
 int /*<<< orphan*/  output_damage_whole_container (struct sway_output*,struct sway_container*) ; 
 TYPE_2__* root ; 

void container_damage_whole(struct sway_container *container) {
	for (int i = 0; i < root->outputs->length; ++i) {
		struct sway_output *output = root->outputs->items[i];
		output_damage_whole_container(output, container);
	}
}