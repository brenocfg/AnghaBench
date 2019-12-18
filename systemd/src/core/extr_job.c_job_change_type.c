#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  id; } ;
struct TYPE_5__ {int /*<<< orphan*/  type; TYPE_2__* unit; } ;
typedef  int /*<<< orphan*/  JobType ;
typedef  TYPE_1__ Job ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  job_type_to_string (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_unit_debug (TYPE_2__*,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void job_change_type(Job *j, JobType newtype) {
        assert(j);

        log_unit_debug(j->unit,
                       "Converting job %s/%s -> %s/%s",
                       j->unit->id, job_type_to_string(j->type),
                       j->unit->id, job_type_to_string(newtype));

        j->type = newtype;
}