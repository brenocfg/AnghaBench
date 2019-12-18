#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_9__ {int /*<<< orphan*/  next_elapse_monotonic_or_boottime; } ;
typedef  TYPE_1__ sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;
typedef  TYPE_1__ sd_bus ;
typedef  TYPE_1__ Timer ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  TIMER_MONOTONIC_CLOCK (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int sd_bus_message_append (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ usec_shift_clock (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int property_get_next_elapse_monotonic(
                sd_bus *bus,
                const char *path,
                const char *interface,
                const char *property,
                sd_bus_message *reply,
                void *userdata,
                sd_bus_error *error) {

        Timer *t = userdata;

        assert(bus);
        assert(reply);
        assert(t);

        return sd_bus_message_append(reply, "t",
                                     (uint64_t) usec_shift_clock(t->next_elapse_monotonic_or_boottime,
                                                                 TIMER_MONOTONIC_CLOCK(t), CLOCK_MONOTONIC));
}