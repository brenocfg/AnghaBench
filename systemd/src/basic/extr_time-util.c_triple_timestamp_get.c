#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* boottime; void* monotonic; void* realtime; } ;
typedef  TYPE_1__ triple_timestamp ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_BOOTTIME ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 void* USEC_INFINITY ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ clock_boottime_supported () ; 
 void* now (int /*<<< orphan*/ ) ; 

triple_timestamp* triple_timestamp_get(triple_timestamp *ts) {
        assert(ts);

        ts->realtime = now(CLOCK_REALTIME);
        ts->monotonic = now(CLOCK_MONOTONIC);
        ts->boottime = clock_boottime_supported() ? now(CLOCK_BOOTTIME) : USEC_INFINITY;

        return ts;
}