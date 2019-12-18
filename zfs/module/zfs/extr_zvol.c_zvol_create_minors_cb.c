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
typedef  scalar_t__ uint64_t ;
struct TYPE_5__ {char* name; scalar_t__ error; int /*<<< orphan*/ * list; } ;
typedef  TYPE_1__ minors_job_t ;
typedef  int /*<<< orphan*/  list_t ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT0 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DS_FIND_SNAPSHOTS ; 
 int /*<<< orphan*/  KM_SLEEP ; 
 int /*<<< orphan*/  MUTEX_HELD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  TQ_SLEEP ; 
 scalar_t__ ZFS_SNAPDEV_VISIBLE ; 
 int dmu_objset_find (char const*,int /*<<< orphan*/ ,void*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dprintf (char*,char const*) ; 
 int dsl_prop_get_integer (char const*,char*,scalar_t__*,int /*<<< orphan*/ *) ; 
 TYPE_1__* kmem_alloc (int,int /*<<< orphan*/ ) ; 
 char* kmem_strdup (char const*) ; 
 int /*<<< orphan*/  list_insert_tail (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  spa_namespace_lock ; 
 scalar_t__ strchr (char const*,char) ; 
 int /*<<< orphan*/  system_taskq ; 
 int /*<<< orphan*/  taskq_dispatch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zvol_create_snap_minor_cb ; 
 int /*<<< orphan*/  zvol_prefetch_minors_impl ; 

__attribute__((used)) static int
zvol_create_minors_cb(const char *dsname, void *arg)
{
	uint64_t snapdev;
	int error;
	list_t *minors_list = arg;

	ASSERT0(MUTEX_HELD(&spa_namespace_lock));

	error = dsl_prop_get_integer(dsname, "snapdev", &snapdev, NULL);
	if (error)
		return (0);

	/*
	 * Given the name and the 'snapdev' property, create device minor nodes
	 * with the linkages to zvols/snapshots as needed.
	 * If the name represents a zvol, create a minor node for the zvol, then
	 * check if its snapshots are 'visible', and if so, iterate over the
	 * snapshots and create device minor nodes for those.
	 */
	if (strchr(dsname, '@') == 0) {
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

		if (snapdev == ZFS_SNAPDEV_VISIBLE) {
			/*
			 * traverse snapshots only, do not traverse children,
			 * and skip the 'dsname'
			 */
			error = dmu_objset_find(dsname,
			    zvol_create_snap_minor_cb, (void *)job,
			    DS_FIND_SNAPSHOTS);
		}
	} else {
		dprintf("zvol_create_minors_cb(): %s is not a zvol name\n",
		    dsname);
	}

	return (0);
}