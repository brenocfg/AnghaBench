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
struct check_items_order_data {int /*<<< orphan*/  done_playing; } ;

/* Variables and functions */
 int /*<<< orphan*/  sched_yield () ; 

__attribute__((used)) static inline void wait_queued_items(struct check_items_order_data *check)
{
    // Wait dummily for check_items_order_callback() to flag 'done_playing':
    while (!check->done_playing)
        sched_yield();
}