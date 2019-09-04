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
struct stats {int /*<<< orphan*/  sd; } ;

/* Variables and functions */
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stats_enabled ; 

__attribute__((used)) static void
stats_stop_aggregator(struct stats *st)
{
    if (!stats_enabled) {
        return;
    }

    close(st->sd);
}