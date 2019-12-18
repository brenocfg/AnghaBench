#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int end; int start; } ;
struct TYPE_5__ {int start; int end; } ;
struct TYPE_7__ {TYPE_2__ dusk; TYPE_1__ dawn; } ;
typedef  TYPE_3__ transition_scheme_t ;
typedef  int /*<<< orphan*/  period_t ;

/* Variables and functions */
 int /*<<< orphan*/  PERIOD_DAYTIME ; 
 int /*<<< orphan*/  PERIOD_NIGHT ; 
 int /*<<< orphan*/  PERIOD_TRANSITION ; 

__attribute__((used)) static period_t
get_period_from_time(const transition_scheme_t *transition, int time_offset)
{
	if (time_offset < transition->dawn.start ||
	    time_offset >= transition->dusk.end) {
		return PERIOD_NIGHT;
	} else if (time_offset >= transition->dawn.end &&
		   time_offset < transition->dusk.start) {
		return PERIOD_DAYTIME;
	} else {
		return PERIOD_TRANSITION;
	}
}