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
struct sway_output {int dummy; } ;
struct sway_container {TYPE_1__* outputs; } ;
struct TYPE_2__ {int length; struct sway_output** items; } ;

/* Variables and functions */

struct sway_output *container_get_effective_output(struct sway_container *con) {
	if (con->outputs->length == 0) {
		return NULL;
	}
	return con->outputs->items[con->outputs->length - 1];
}