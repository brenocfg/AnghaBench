#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int progress_percent; int error; int /*<<< orphan*/  (* on_finished ) (TYPE_1__*) ;int /*<<< orphan*/  state; int /*<<< orphan*/  url; } ;
typedef  TYPE_1__ PullJob ;

/* Variables and functions */
 scalar_t__ IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PULL_JOB_DONE ; 
 int /*<<< orphan*/  PULL_JOB_FAILED ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 

__attribute__((used)) static void pull_job_finish(PullJob *j, int ret) {
        assert(j);

        if (IN_SET(j->state, PULL_JOB_DONE, PULL_JOB_FAILED))
                return;

        if (ret == 0) {
                j->state = PULL_JOB_DONE;
                j->progress_percent = 100;
                log_info("Download of %s complete.", j->url);
        } else {
                j->state = PULL_JOB_FAILED;
                j->error = ret;
        }

        if (j->on_finished)
                j->on_finished(j);
}