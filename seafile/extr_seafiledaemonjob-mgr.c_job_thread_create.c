#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/ * pipefd; TYPE_1__* manager; } ;
struct TYPE_8__ {int /*<<< orphan*/  ev_base; } ;
struct TYPE_7__ {int /*<<< orphan*/  thread_pool; TYPE_2__* session; } ;
typedef  TYPE_2__ SeafileSession ;
typedef  TYPE_3__ SeafJob ;

/* Variables and functions */
 int /*<<< orphan*/  EV_READ ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  event_base_once (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_thread_pool_push (int /*<<< orphan*/ ,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  job_done_cb ; 
 scalar_t__ seaf_pipe (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

int
job_thread_create (SeafJob *job)
{
    SeafileSession *session = job->manager->session;

    if (seaf_pipe (job->pipefd) < 0) {
        seaf_warning ("[Job Manager] pipe error: %s\n", strerror(errno));
        return -1;
    }

    g_thread_pool_push (job->manager->thread_pool, job, NULL);

    event_base_once (session->ev_base, job->pipefd[0], EV_READ, job_done_cb, job, NULL);

    return 0;
}