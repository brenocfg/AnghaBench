#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  elem; } ;
struct TYPE_5__ {int /*<<< orphan*/  elem; } ;
struct stats {int aggregate; scalar_t__ updated; TYPE_1__ current; TYPE_3__ shadow; } ;

/* Variables and functions */
 int /*<<< orphan*/  LOG_PVERB ; 
 int /*<<< orphan*/  array_swap (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  log_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stats_enabled ; 
 int /*<<< orphan*/  stats_pool_reset (TYPE_1__*) ; 

void
stats_swap(struct stats *st)
{
    if (!stats_enabled) {
        return;
    }

    if (st->aggregate == 1) {
        log_debug(LOG_PVERB, "skip swap of current %p shadow %p as aggregator "
                  "is busy", st->current.elem, st->shadow.elem);
        return;
    }

    if (st->updated == 0) {
        log_debug(LOG_PVERB, "skip swap of current %p shadow %p as there is "
                  "nothing new", st->current.elem, st->shadow.elem);
        return;
    }

    log_debug(LOG_PVERB, "swap stats current %p shadow %p", st->current.elem,
              st->shadow.elem);

    array_swap(&st->current, &st->shadow);

    /*
     * Reset current (a) stats before giving it back to generator to keep
     * stats addition idempotent
     */
    stats_pool_reset(&st->current);
    st->updated = 0;

    st->aggregate = 1;
}