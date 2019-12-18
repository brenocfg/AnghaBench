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
struct TYPE_5__ {scalar_t__ monotonic; scalar_t__ realtime; } ;
typedef  TYPE_1__ dual_timestamp ;

/* Variables and functions */
 scalar_t__ MIN (scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ timestamp_is_set (scalar_t__) ; 

__attribute__((used)) static usec_t calc_next_elapse(dual_timestamp *nw, dual_timestamp *next) {
        usec_t next_elapse;

        assert(nw);
        assert(next);

        if (timestamp_is_set(next->monotonic)) {
                usec_t converted;

                if (next->monotonic > nw->monotonic)
                        converted = nw->realtime + (next->monotonic - nw->monotonic);
                else
                        converted = nw->realtime - (nw->monotonic - next->monotonic);

                if (timestamp_is_set(next->realtime))
                        next_elapse = MIN(converted, next->realtime);
                else
                        next_elapse = converted;

        } else
                next_elapse = next->realtime;

        return next_elapse;
}