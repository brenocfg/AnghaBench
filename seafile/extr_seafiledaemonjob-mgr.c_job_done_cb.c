#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  evutil_socket_t ;
struct TYPE_3__ {int /*<<< orphan*/  result; int /*<<< orphan*/  (* done_func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/ * pipefd; } ;
typedef  TYPE_1__ SeafJob ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  seaf_job_free (TYPE_1__*) ; 
 int /*<<< orphan*/  seaf_pipe_close (int /*<<< orphan*/ ) ; 
 int seaf_pipe_readn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
job_done_cb (evutil_socket_t fd, short event, void *vdata)
{
    SeafJob *job = vdata;
    char buf[1];

    if (seaf_pipe_readn (job->pipefd[0], buf, 1) != 1) {
        seaf_warning ("[Job Manager] read pipe error: %s\n", strerror(errno));
    }
    seaf_pipe_close (job->pipefd[0]);
    seaf_pipe_close (job->pipefd[1]);
    if (job->done_func) {
        job->done_func (job->result);
    }

    seaf_job_free (job);
}