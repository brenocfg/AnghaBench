#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
struct stats_server {int /*<<< orphan*/  metric; } ;
struct TYPE_3__ {int /*<<< orphan*/  elem; } ;
struct stats_pool {TYPE_1__ server; int /*<<< orphan*/  metric; } ;
struct stats {scalar_t__ aggregate; TYPE_1__ sum; TYPE_1__ shadow; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_PVERB ; 
 void* array_get (TYPE_1__*,scalar_t__) ; 
 scalar_t__ array_n (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stats_aggregate_metric (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
stats_aggregate(struct stats *st)
{
    uint32_t i;

    if (st->aggregate == 0) {
        log_debug(LOG_PVERB, "skip aggregate of shadow %p to sum %p as "
                  "generator is slow", st->shadow.elem, st->sum.elem);
        return;
    }

    log_debug(LOG_PVERB, "aggregate stats shadow %p to sum %p", st->shadow.elem,
              st->sum.elem);

    for (i = 0; i < array_n(&st->shadow); i++) {
        struct stats_pool *stp1, *stp2;
        uint32_t j;

        stp1 = array_get(&st->shadow, i);
        stp2 = array_get(&st->sum, i);
        stats_aggregate_metric(&stp2->metric, &stp1->metric);

        for (j = 0; j < array_n(&stp1->server); j++) {
            struct stats_server *sts1, *sts2;

            sts1 = array_get(&stp1->server, j);
            sts2 = array_get(&stp2->server, j);
            stats_aggregate_metric(&sts2->metric, &sts1->metric);
        }
    }

    st->aggregate = 0;
}