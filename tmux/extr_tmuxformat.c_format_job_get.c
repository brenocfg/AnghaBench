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
typedef  scalar_t__ time_t ;
struct format_tree {int flags; TYPE_1__* client; int /*<<< orphan*/  tag; } ;
struct format_job_tree {int dummy; } ;
struct format_job {char const* cmd; char* out; scalar_t__ last; int status; scalar_t__ updated; int /*<<< orphan*/ * job; int /*<<< orphan*/ * expanded; int /*<<< orphan*/  tag; TYPE_1__* client; } ;
struct TYPE_2__ {struct format_job_tree* jobs; } ;

/* Variables and functions */
 int FORMAT_FORCE ; 
 int FORMAT_STATUS ; 
 int /*<<< orphan*/  JOB_NOWAIT ; 
 struct format_job* RB_FIND (int /*<<< orphan*/ ,struct format_job_tree*,struct format_job*) ; 
 int /*<<< orphan*/  RB_INIT (struct format_job_tree*) ; 
 int /*<<< orphan*/  RB_INSERT (int /*<<< orphan*/ ,struct format_job_tree*,struct format_job*) ; 
 char* format_expand (struct format_tree*,char const*) ; 
 int /*<<< orphan*/  format_job_complete ; 
 int /*<<< orphan*/  format_job_tree ; 
 int /*<<< orphan*/  format_job_update ; 
 struct format_job_tree format_jobs ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  job_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * job_run (char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct format_job*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  server_client_get_cwd (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ strcmp (char*,int /*<<< orphan*/ *) ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xasprintf (char**,char*,char const*) ; 
 struct format_job* xcalloc (int,int) ; 
 struct format_job_tree* xmalloc (int) ; 
 void* xstrdup (char const*) ; 

__attribute__((used)) static char *
format_job_get(struct format_tree *ft, const char *cmd)
{
	struct format_job_tree	*jobs;
	struct format_job	 fj0, *fj;
	time_t			 t;
	char			*expanded;
	int			 force;

	if (ft->client == NULL)
		jobs = &format_jobs;
	else if (ft->client->jobs != NULL)
		jobs = ft->client->jobs;
	else {
		jobs = ft->client->jobs = xmalloc(sizeof *ft->client->jobs);
		RB_INIT(jobs);
	}

	fj0.tag = ft->tag;
	fj0.cmd = cmd;
	if ((fj = RB_FIND(format_job_tree, jobs, &fj0)) == NULL) {
		fj = xcalloc(1, sizeof *fj);
		fj->client = ft->client;
		fj->tag = ft->tag;
		fj->cmd = xstrdup(cmd);
		fj->expanded = NULL;

		xasprintf(&fj->out, "<'%s' not ready>", fj->cmd);

		RB_INSERT(format_job_tree, jobs, fj);
	}

	expanded = format_expand(ft, cmd);
	if (fj->expanded == NULL || strcmp(expanded, fj->expanded) != 0) {
		free((void *)fj->expanded);
		fj->expanded = xstrdup(expanded);
		force = 1;
	} else
		force = (ft->flags & FORMAT_FORCE);

	t = time(NULL);
	if (force && fj->job != NULL)
	       job_free(fj->job);
	if (force || (fj->job == NULL && fj->last != t)) {
		fj->job = job_run(expanded, NULL,
		    server_client_get_cwd(ft->client, NULL), format_job_update,
		    format_job_complete, NULL, fj, JOB_NOWAIT);
		if (fj->job == NULL) {
			free(fj->out);
			xasprintf(&fj->out, "<'%s' didn't start>", fj->cmd);
		}
		fj->last = t;
		fj->updated = 0;
	}

	if (ft->flags & FORMAT_STATUS)
		fj->status = 1;

	free(expanded);
	return (format_expand(ft, fj->out));
}