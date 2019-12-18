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
struct TYPE_3__ {double low; double high; } ;
typedef  TYPE_1__ transition_scheme_t ;
typedef  int /*<<< orphan*/  period_t ;

/* Variables and functions */
 int /*<<< orphan*/  PERIOD_DAYTIME ; 
 int /*<<< orphan*/  PERIOD_NIGHT ; 
 int /*<<< orphan*/  PERIOD_TRANSITION ; 

__attribute__((used)) static period_t
get_period_from_elevation(
	const transition_scheme_t *transition, double elevation)
{
	if (elevation < transition->low) {
		return PERIOD_NIGHT;
	} else if (elevation < transition->high) {
		return PERIOD_TRANSITION;
	} else {
		return PERIOD_DAYTIME;
	}
}