#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  location_t ;
struct TYPE_3__ {int /*<<< orphan*/  loc; } ;
typedef  TYPE_1__ location_manual_state_t ;

/* Variables and functions */

__attribute__((used)) static int
location_manual_handle(
	location_manual_state_t *state, location_t *location, int *available)
{
	*location = state->loc;
	*available = 1;

	return 0;
}