#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct job {int pid; int fd; int /*<<< orphan*/ * event; int /*<<< orphan*/ * data; int /*<<< orphan*/  (* freecb ) (int /*<<< orphan*/ *) ;struct job* cmd; } ;

/* Variables and functions */
 int /*<<< orphan*/  LIST_REMOVE (struct job*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  bufferevent_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  close (int) ; 
 int /*<<< orphan*/  entry ; 
 int /*<<< orphan*/  free (struct job*) ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*,struct job*,struct job*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

void
job_free(struct job *job)
{
	log_debug("free job %p: %s", job, job->cmd);

	LIST_REMOVE(job, entry);
	free(job->cmd);

	if (job->freecb != NULL && job->data != NULL)
		job->freecb(job->data);

	if (job->pid != -1)
		kill(job->pid, SIGTERM);
	if (job->event != NULL)
		bufferevent_free(job->event);
	if (job->fd != -1)
		close(job->fd);

	free(job);
}