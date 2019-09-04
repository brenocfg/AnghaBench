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
typedef  scalar_t__ uint32_t ;
struct stats_server {int /*<<< orphan*/  metric; } ;
struct array {int dummy; } ;
struct stats_pool {struct array server; int /*<<< orphan*/  metric; } ;

/* Variables and functions */
 void* array_get (struct array*,scalar_t__) ; 
 scalar_t__ array_n (struct array*) ; 
 int /*<<< orphan*/  stats_metric_reset (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
stats_pool_reset(struct array *stats_pool)
{
    uint32_t i, npool;

    npool = array_n(stats_pool);

    for (i = 0; i < npool; i++) {
        struct stats_pool *stp = array_get(stats_pool, i);
        uint32_t j, nserver;

        stats_metric_reset(&stp->metric);

        nserver = array_n(&stp->server);
        for (j = 0; j < nserver; j++) {
            struct stats_server *sts = array_get(&stp->server, j);
            stats_metric_reset(&sts->metric);
        }
    }
}