#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct unit_times {scalar_t__ activated; } ;
struct boot_times {scalar_t__ finish_time; } ;

/* Variables and functions */

__attribute__((used)) static bool times_in_range(const struct unit_times *times, const struct boot_times *boot) {
        return times && times->activated > 0 && times->activated <= boot->finish_time;
}