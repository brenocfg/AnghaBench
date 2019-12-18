#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int in_gc_queue; TYPE_2__* unit; } ;
struct TYPE_9__ {TYPE_1__* manager; } ;
struct TYPE_8__ {int /*<<< orphan*/  gc_job_queue; } ;
typedef  TYPE_3__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_PREPEND (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  gc_queue ; 
 int /*<<< orphan*/  job_may_gc (TYPE_3__*) ; 

void job_add_to_gc_queue(Job *j) {
        assert(j);

        if (j->in_gc_queue)
                return;

        if (!job_may_gc(j))
                return;

        LIST_PREPEND(gc_queue, j->unit->manager->gc_job_queue, j);
        j->in_gc_queue = true;
}