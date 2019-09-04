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
struct sway_seat {int dummy; } ;
struct TYPE_3__ {struct sway_seat* seat; } ;
struct TYPE_4__ {TYPE_1__ handler_context; } ;

/* Variables and functions */
 TYPE_2__* config ; 
 struct sway_seat* input_manager_get_default_seat () ; 

struct sway_seat *input_manager_current_seat(void) {
	struct sway_seat *seat = config->handler_context.seat;
	if (!seat) {
		seat = input_manager_get_default_seat();
	}
	return seat;
}