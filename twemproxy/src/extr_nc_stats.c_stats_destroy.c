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
struct stats {int /*<<< orphan*/  current; int /*<<< orphan*/  shadow; int /*<<< orphan*/  sum; } ;

/* Variables and functions */
 int /*<<< orphan*/  nc_free (struct stats*) ; 
 int /*<<< orphan*/  stats_destroy_buf (struct stats*) ; 
 int /*<<< orphan*/  stats_pool_unmap (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stats_stop_aggregator (struct stats*) ; 

void
stats_destroy(struct stats *st)
{
    stats_stop_aggregator(st);
    stats_pool_unmap(&st->sum);
    stats_pool_unmap(&st->shadow);
    stats_pool_unmap(&st->current);
    stats_destroy_buf(st);
    nc_free(st);
}