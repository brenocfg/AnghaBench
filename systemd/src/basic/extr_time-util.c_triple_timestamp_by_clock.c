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
typedef  int /*<<< orphan*/  usec_t ;
struct TYPE_3__ {int /*<<< orphan*/  boottime; int /*<<< orphan*/  monotonic; int /*<<< orphan*/  realtime; } ;
typedef  TYPE_1__ triple_timestamp ;
typedef  int clockid_t ;

/* Variables and functions */
#define  CLOCK_BOOTTIME 132 
#define  CLOCK_BOOTTIME_ALARM 131 
#define  CLOCK_MONOTONIC 130 
#define  CLOCK_REALTIME 129 
#define  CLOCK_REALTIME_ALARM 128 
 int /*<<< orphan*/  USEC_INFINITY ; 

usec_t triple_timestamp_by_clock(triple_timestamp *ts, clockid_t clock) {

        switch (clock) {

        case CLOCK_REALTIME:
        case CLOCK_REALTIME_ALARM:
                return ts->realtime;

        case CLOCK_MONOTONIC:
                return ts->monotonic;

        case CLOCK_BOOTTIME:
        case CLOCK_BOOTTIME_ALARM:
                return ts->boottime;

        default:
                return USEC_INFINITY;
        }
}