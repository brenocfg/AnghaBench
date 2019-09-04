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
struct fps_counter {int started; } ;

/* Variables and functions */

void
fps_counter_init(struct fps_counter *counter) {
    counter->started = false;
    // no need to initialize the other fields, they are meaningful only when
    // started is true
}