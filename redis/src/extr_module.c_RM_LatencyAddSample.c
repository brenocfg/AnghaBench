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
struct TYPE_2__ {scalar_t__ latency_monitor_threshold; } ;

/* Variables and functions */
 int /*<<< orphan*/  latencyAddSample (char const*,scalar_t__) ; 
 TYPE_1__ server ; 

void RM_LatencyAddSample(const char *event, mstime_t latency) {
    if (latency >= server.latency_monitor_threshold)
        latencyAddSample(event, latency);
}