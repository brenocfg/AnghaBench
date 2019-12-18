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
typedef  size_t BusFocus ;

/* Variables and functions */
 size_t _BUS_FOCUS_MAX ; 
 int /*<<< orphan*/ * buses ; 
 int /*<<< orphan*/  sd_bus_flush_close_unref (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void release_busses(void) {
        BusFocus w;

        for (w = 0; w < _BUS_FOCUS_MAX; w++)
                buses[w] = sd_bus_flush_close_unref(buses[w]);
}