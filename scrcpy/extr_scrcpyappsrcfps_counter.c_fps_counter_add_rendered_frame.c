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
struct fps_counter {int /*<<< orphan*/  nr_rendered; } ;

/* Variables and functions */
 int /*<<< orphan*/  check_expired (struct fps_counter*) ; 

void
fps_counter_add_rendered_frame(struct fps_counter *counter) {
    check_expired(counter);
    ++counter->nr_rendered;
}