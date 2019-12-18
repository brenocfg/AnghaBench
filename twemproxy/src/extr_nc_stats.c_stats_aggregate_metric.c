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
typedef  scalar_t__ uint32_t ;
struct TYPE_2__ {int /*<<< orphan*/  timestamp; int /*<<< orphan*/  counter; } ;
struct stats_metric {int type; TYPE_1__ value; } ;
struct array {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT (int) ; 
 int /*<<< orphan*/  NOT_REACHED () ; 
#define  STATS_COUNTER 130 
#define  STATS_GAUGE 129 
#define  STATS_TIMESTAMP 128 
 struct stats_metric* array_get (struct array*,scalar_t__) ; 
 scalar_t__ array_n (struct array*) ; 

__attribute__((used)) static void
stats_aggregate_metric(struct array *dst, struct array *src)
{
    uint32_t i;

    for (i = 0; i < array_n(src); i++) {
        struct stats_metric *stm1, *stm2;

        stm1 = array_get(src, i);
        stm2 = array_get(dst, i);

        ASSERT(stm1->type == stm2->type);

        switch (stm1->type) {
        case STATS_COUNTER:
            stm2->value.counter += stm1->value.counter;
            break;

        case STATS_GAUGE:
            stm2->value.counter += stm1->value.counter;
            break;

        case STATS_TIMESTAMP:
            if (stm1->value.timestamp) {
                stm2->value.timestamp = stm1->value.timestamp;
            }
            break;

        default:
            NOT_REACHED();
        }
    }
}