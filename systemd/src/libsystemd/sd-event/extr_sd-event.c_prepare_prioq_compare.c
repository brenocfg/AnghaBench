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
struct TYPE_2__ {scalar_t__ enabled; int /*<<< orphan*/  priority; int /*<<< orphan*/  prepare_iteration; int /*<<< orphan*/  prepare; } ;
typedef  TYPE_1__ sd_event_source ;

/* Variables and functions */
 int CMP (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ SD_EVENT_OFF ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int prepare_prioq_compare(const void *a, const void *b) {
        const sd_event_source *x = a, *y = b;
        int r;

        assert(x->prepare);
        assert(y->prepare);

        /* Enabled ones first */
        if (x->enabled != SD_EVENT_OFF && y->enabled == SD_EVENT_OFF)
                return -1;
        if (x->enabled == SD_EVENT_OFF && y->enabled != SD_EVENT_OFF)
                return 1;

        /* Move most recently prepared ones last, so that we can stop
         * preparing as soon as we hit one that has already been
         * prepared in the current iteration */
        r = CMP(x->prepare_iteration, y->prepare_iteration);
        if (r != 0)
                return r;

        /* Lower priority values first */
        return CMP(x->priority, y->priority);
}