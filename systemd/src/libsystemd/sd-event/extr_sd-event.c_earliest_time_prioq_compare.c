#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  next; } ;
struct TYPE_4__ {scalar_t__ type; scalar_t__ enabled; TYPE_1__ time; scalar_t__ pending; } ;
typedef  TYPE_2__ sd_event_source ;

/* Variables and functions */
 int CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int EVENT_SOURCE_IS_TIME (scalar_t__) ; 
 scalar_t__ SD_EVENT_OFF ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int earliest_time_prioq_compare(const void *a, const void *b) {
        const sd_event_source *x = a, *y = b;

        assert(EVENT_SOURCE_IS_TIME(x->type));
        assert(x->type == y->type);

        /* Enabled ones first */
        if (x->enabled != SD_EVENT_OFF && y->enabled == SD_EVENT_OFF)
                return -1;
        if (x->enabled == SD_EVENT_OFF && y->enabled != SD_EVENT_OFF)
                return 1;

        /* Move the pending ones to the end */
        if (!x->pending && y->pending)
                return -1;
        if (x->pending && !y->pending)
                return 1;

        /* Order by time */
        return CMP(x->time.next, y->time.next);
}