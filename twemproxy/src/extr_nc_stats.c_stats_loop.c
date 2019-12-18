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

/* Variables and functions */
 int /*<<< orphan*/  event_loop_stats (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  stats_loop_callback ; 

__attribute__((used)) static void *
stats_loop(void *arg)
{
    event_loop_stats(stats_loop_callback, arg);
    return NULL;
}