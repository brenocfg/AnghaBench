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
struct TYPE_2__ {int /*<<< orphan*/ * pipefd; int /*<<< orphan*/  data; int /*<<< orphan*/  (* thread_func ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  result; } ;
typedef  TYPE_1__ SeafJob ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int seaf_pipe_writen (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
job_thread_wrapper (void *vdata, void *unused)
{
    SeafJob *job = vdata;
   
    job->result = job->thread_func (job->data);
    if (seaf_pipe_writen (job->pipefd[1], "a", 1) != 1) {
        seaf_warning ("[Job Manager] write to pipe error: %s\n", strerror(errno));
    }
}