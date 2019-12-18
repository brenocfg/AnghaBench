#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  netns_storage_socket; struct TYPE_13__* var_tmp_dir; struct TYPE_13__* tmp_dir; struct TYPE_13__* id; TYPE_1__* manager; } ;
struct TYPE_12__ {int /*<<< orphan*/  exec_runtime_by_id; } ;
typedef  TYPE_2__ ExecRuntime ;

/* Variables and functions */
 int asynchronous_job (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  hashmap_remove (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  log_debug (char*,TYPE_2__*) ; 
 int /*<<< orphan*/  log_warning_errno (int,char*,TYPE_2__*) ; 
 TYPE_2__* mfree (TYPE_2__*) ; 
 int /*<<< orphan*/  remove_tmpdir_thread ; 
 int /*<<< orphan*/  safe_close_pair (int /*<<< orphan*/ ) ; 

__attribute__((used)) static ExecRuntime* exec_runtime_free(ExecRuntime *rt, bool destroy) {
        int r;

        if (!rt)
                return NULL;

        if (rt->manager)
                (void) hashmap_remove(rt->manager->exec_runtime_by_id, rt->id);

        /* When destroy is true, then rm_rf tmp_dir and var_tmp_dir. */
        if (destroy && rt->tmp_dir) {
                log_debug("Spawning thread to nuke %s", rt->tmp_dir);

                r = asynchronous_job(remove_tmpdir_thread, rt->tmp_dir);
                if (r < 0) {
                        log_warning_errno(r, "Failed to nuke %s: %m", rt->tmp_dir);
                        free(rt->tmp_dir);
                }

                rt->tmp_dir = NULL;
        }

        if (destroy && rt->var_tmp_dir) {
                log_debug("Spawning thread to nuke %s", rt->var_tmp_dir);

                r = asynchronous_job(remove_tmpdir_thread, rt->var_tmp_dir);
                if (r < 0) {
                        log_warning_errno(r, "Failed to nuke %s: %m", rt->var_tmp_dir);
                        free(rt->var_tmp_dir);
                }

                rt->var_tmp_dir = NULL;
        }

        rt->id = mfree(rt->id);
        rt->tmp_dir = mfree(rt->tmp_dir);
        rt->var_tmp_dir = mfree(rt->var_tmp_dir);
        safe_close_pair(rt->netns_storage_socket);
        return mfree(rt);
}