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
typedef  int /*<<< orphan*/  pthread_t ;
typedef  int /*<<< orphan*/  pthread_attr_t ;
struct TYPE_6__ {TYPE_1__* priv; } ;
struct TYPE_5__ {int /*<<< orphan*/ * lock_office_job_queue; } ;
typedef  TYPE_2__ SeafRepoManager ;

/* Variables and functions */
 int /*<<< orphan*/  PTHREAD_CREATE_DETACHED ; 
 int /*<<< orphan*/  cleanup_deleted_stores ; 
 int /*<<< orphan*/  lock_office_file_worker ; 
 int /*<<< orphan*/  pthread_attr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_attr_setdetachstate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int) ; 
 int /*<<< orphan*/  watch_repos (TYPE_2__*) ; 

int
seaf_repo_manager_start (SeafRepoManager *mgr)
{
    pthread_t tid;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    int rc;

    watch_repos (mgr);

    rc = pthread_create (&tid, &attr, cleanup_deleted_stores, NULL);
    if (rc != 0) {
        seaf_warning ("Failed to start cleanup thread: %s\n", strerror(rc));
    }

#if defined WIN32 || defined __APPLE__
    rc = pthread_create (&tid, &attr, lock_office_file_worker,
                         mgr->priv->lock_office_job_queue);
    if (rc != 0) {
        seaf_warning ("Failed to start lock office file thread: %s\n", strerror(rc));
    }
#endif

    return 0;
}