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
struct TYPE_5__ {char* name; scalar_t__ error; int /*<<< orphan*/ * list; } ;
typedef  TYPE_1__ minors_job_t ;
typedef  int /*<<< orphan*/  list_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TQ_SLEEP ; 
 int /*<<< orphan*/  dprintf (char*,char const*) ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 char* kmem_strdup (char const*) ; 
 int /*<<< orphan*/  list_insert_tail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 scalar_t__ strchr (char const*,char) ; 
 scalar_t__ strcmp (char const*,char const*) ; 
 int /*<<< orphan*/  system_taskq ; 
 int /*<<< orphan*/  taskq_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_prefetch_minors_impl ; 

__attribute__((used)) static int
zvol_create_snap_minor_cb(const char *dsname, void *arg)
{
	minors_job_t *j = arg;
	list_t *minors_list = j->list;
	const char *name = j->name;

	ASSERT0(MUTEX_HELD(&spa_namespace_lock));

	/* skip the designated dataset */
	if (name && strcmp(dsname, name) == 0)
		return (0);

	/* at this point, the dsname should name a snapshot */
	if (strchr(dsname, '@') == 0) {
		dprintf("zvol_create_snap_minor_cb(): "
		    "%s is not a snapshot name\n", dsname);
	} else {
		minors_job_t *job;
		char *n = kmem_strdup(dsname);
		if (n == NULL)
			return (0);

		job = kmem_alloc(sizeof (minors_job_t), KM_SLEEP);
		job->name = n;
		job->list = minors_list;
		job->error = 0;
		list_insert_tail(minors_list, job);
		/* don't care if dispatch fails, because job->error is 0 */
		taskq_dispatch(system_taskq, zvol_prefetch_minors_impl, job,
		    TQ_SLEEP);
	}

	return (0);
}