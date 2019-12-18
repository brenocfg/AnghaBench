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
typedef  scalar_t__ usec_t ;
typedef  scalar_t__ int64_t ;
struct TYPE_5__ {scalar_t__ realtime; scalar_t__ monotonic; } ;
typedef  TYPE_1__ dual_timestamp ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  CLOCK_REALTIME ; 
 scalar_t__ USEC_INFINITY ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 
 scalar_t__ usec_sub_signed (scalar_t__,scalar_t__) ; 

dual_timestamp* dual_timestamp_from_monotonic(dual_timestamp *ts, usec_t u) {
        int64_t delta;
        assert(ts);

        if (u == USEC_INFINITY) {
                ts->realtime = ts->monotonic = USEC_INFINITY;
                return ts;
        }

        ts->monotonic = u;
        delta = (int64_t) now(CLOCK_MONOTONIC) - (int64_t) u;
        ts->realtime = usec_sub_signed(now(CLOCK_REALTIME), delta);

        return ts;
}