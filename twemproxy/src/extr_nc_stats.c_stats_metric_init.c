#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {long long counter; long long timestamp; } ;
struct stats_metric {int type; TYPE_1__ value; } ;

/* Variables and functions */
 int /*<<< orphan*/  NOT_REACHED () ; 
#define  STATS_COUNTER 130 
#define  STATS_GAUGE 129 
#define  STATS_TIMESTAMP 128 

__attribute__((used)) static void
stats_metric_init(struct stats_metric *stm)
{
    switch (stm->type) {
    case STATS_COUNTER:
        stm->value.counter = 0LL;
        break;

    case STATS_GAUGE:
        stm->value.counter = 0LL;
        break;

    case STATS_TIMESTAMP:
        stm->value.timestamp = 0LL;
        break;

    default:
        NOT_REACHED();
    }
}