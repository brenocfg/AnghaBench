#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int display_count; } ;
typedef  TYPE_1__ quartz_state_t ;
typedef  int /*<<< orphan*/  color_setting_t ;

/* Variables and functions */
 int /*<<< orphan*/  quartz_set_temperature_for_display (TYPE_1__*,int,int /*<<< orphan*/  const*,int) ; 

__attribute__((used)) static int
quartz_set_temperature(
	quartz_state_t *state, const color_setting_t *setting, int preserve)
{
	for (int i = 0; i < state->display_count; i++) {
		quartz_set_temperature_for_display(
			state, i, setting, preserve);
	}

	return 0;
}