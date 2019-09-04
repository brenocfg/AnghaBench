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
typedef  scalar_t__ mstime_t ;
struct TYPE_2__ {scalar_t__ previous_time; int tilt; scalar_t__ tilt_start_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  LL_WARNING ; 
 scalar_t__ SENTINEL_TILT_TRIGGER ; 
 scalar_t__ mstime () ; 
 TYPE_1__ sentinel ; 
 int /*<<< orphan*/  sentinelEvent (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char*) ; 

void sentinelCheckTiltCondition(void) {
    mstime_t now = mstime();
    mstime_t delta = now - sentinel.previous_time;

    if (delta < 0 || delta > SENTINEL_TILT_TRIGGER) {
        sentinel.tilt = 1;
        sentinel.tilt_start_time = mstime();
        sentinelEvent(LL_WARNING,"+tilt",NULL,"#tilt mode entered");
    }
    sentinel.previous_time = mstime();
}