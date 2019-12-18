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
struct stats {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  stats_aggregate (struct stats*) ; 
 int /*<<< orphan*/  stats_send_rsp (struct stats*) ; 

__attribute__((used)) static void
stats_loop_callback(void *arg1, void *arg2)
{
    struct stats *st = arg1;
    int n = *((int *)arg2);

    /* aggregate stats from shadow (b) -> sum (c) */
    stats_aggregate(st);

    if (n == 0) {
        return;
    }

    /* send aggregate stats sum (c) to collector */
    stats_send_rsp(st);
}