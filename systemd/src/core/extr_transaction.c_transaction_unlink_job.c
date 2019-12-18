#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_11__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  type; TYPE_8__* unit; TYPE_9__* object_list; TYPE_9__* subject_list; TYPE_11__* transaction_next; TYPE_1__* transaction_prev; int /*<<< orphan*/  jobs; } ;
typedef  TYPE_2__ Transaction ;
struct TYPE_19__ {TYPE_2__* subject; scalar_t__ matters; } ;
struct TYPE_18__ {int /*<<< orphan*/  id; } ;
struct TYPE_16__ {TYPE_11__* transaction_next; } ;
struct TYPE_15__ {TYPE_1__* transaction_prev; } ;
typedef  TYPE_2__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  hashmap_remove_value (int /*<<< orphan*/ ,TYPE_8__*,TYPE_2__*) ; 
 int /*<<< orphan*/  hashmap_replace (int /*<<< orphan*/ ,TYPE_8__*,TYPE_11__*) ; 
 int /*<<< orphan*/  job_dependency_free (TYPE_9__*) ; 
 int /*<<< orphan*/  job_type_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_unit_debug (TYPE_8__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  transaction_delete_job (TYPE_2__*,TYPE_2__*,int) ; 

__attribute__((used)) static void transaction_unlink_job(Transaction *tr, Job *j, bool delete_dependencies) {
        assert(tr);
        assert(j);

        if (j->transaction_prev)
                j->transaction_prev->transaction_next = j->transaction_next;
        else if (j->transaction_next)
                hashmap_replace(tr->jobs, j->unit, j->transaction_next);
        else
                hashmap_remove_value(tr->jobs, j->unit, j);

        if (j->transaction_next)
                j->transaction_next->transaction_prev = j->transaction_prev;

        j->transaction_prev = j->transaction_next = NULL;

        while (j->subject_list)
                job_dependency_free(j->subject_list);

        while (j->object_list) {
                Job *other = j->object_list->matters ? j->object_list->subject : NULL;

                job_dependency_free(j->object_list);

                if (other && delete_dependencies) {
                        log_unit_debug(other->unit,
                                       "Deleting job %s/%s as dependency of job %s/%s",
                                       other->unit->id, job_type_to_string(other->type),
                                       j->unit->id, job_type_to_string(j->type));
                        transaction_delete_job(tr, other, delete_dependencies);
                }
        }
}