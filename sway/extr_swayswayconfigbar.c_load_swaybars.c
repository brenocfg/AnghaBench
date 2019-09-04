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
struct bar_config {int dummy; } ;
struct TYPE_4__ {TYPE_1__* bars; } ;
struct TYPE_3__ {int length; struct bar_config** items; } ;

/* Variables and functions */
 TYPE_2__* config ; 
 int /*<<< orphan*/  load_swaybar (struct bar_config*) ; 

void load_swaybars(void) {
	for (int i = 0; i < config->bars->length; ++i) {
		struct bar_config *bar = config->bars->items[i];
		load_swaybar(bar);
	}
}