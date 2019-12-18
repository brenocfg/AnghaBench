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
struct TYPE_2__ {int /*<<< orphan*/  job_mgr; } ;
typedef  int /*<<< orphan*/  SeafileSession ;

/* Variables and functions */
 int /*<<< orphan*/  cleanup_job_done ; 
 int /*<<< orphan*/  on_start_cleanup_job ; 
 TYPE_1__* seaf ; 
 int /*<<< orphan*/  seaf_job_manager_schedule_job (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
on_start_cleanup (SeafileSession *session)
{
    seaf_job_manager_schedule_job (seaf->job_mgr, 
                                   on_start_cleanup_job, 
                                   cleanup_job_done,
                                   session);
}