#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  size_t UnitType ;
struct TYPE_17__ {int /*<<< orphan*/  (* shutdown ) (TYPE_1__*) ;} ;
struct TYPE_16__ {struct TYPE_16__** prefix; int /*<<< orphan*/  gid_refs; int /*<<< orphan*/  uid_refs; int /*<<< orphan*/  units_requiring_mounts_for; int /*<<< orphan*/  rlimit; int /*<<< orphan*/  switch_root_init; int /*<<< orphan*/  switch_root; int /*<<< orphan*/  cgroup_unit; int /*<<< orphan*/  client_environment; int /*<<< orphan*/  transient_environment; int /*<<< orphan*/  lookup_paths; int /*<<< orphan*/  notify_socket; int /*<<< orphan*/  event; int /*<<< orphan*/  user_lookup_fds; int /*<<< orphan*/  time_change_fd; int /*<<< orphan*/  cgroups_agent_fd; int /*<<< orphan*/  notify_fd; int /*<<< orphan*/  signal_fd; int /*<<< orphan*/  sync_bus_names_event_source; int /*<<< orphan*/  user_lookup_event_source; int /*<<< orphan*/  run_queue_event_source; int /*<<< orphan*/  jobs_in_progress_event_source; int /*<<< orphan*/  timezone_change_event_source; int /*<<< orphan*/  time_change_event_source; int /*<<< orphan*/  cgroups_agent_event_source; int /*<<< orphan*/  notify_event_source; int /*<<< orphan*/  sigchld_event_source; int /*<<< orphan*/  signal_event_source; int /*<<< orphan*/  failed_units; int /*<<< orphan*/  startup_units; int /*<<< orphan*/  run_queue; int /*<<< orphan*/  watch_bus; int /*<<< orphan*/  watch_pids; int /*<<< orphan*/  jobs; int /*<<< orphan*/  units_by_invocation_id; int /*<<< orphan*/  units; int /*<<< orphan*/  dynamic_users; int /*<<< orphan*/  exec_runtime_by_id; int /*<<< orphan*/  objective; } ;
typedef  TYPE_1__ Manager ;
typedef  size_t ExecDirectoryType ;

/* Variables and functions */
 int /*<<< orphan*/  IN_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MANAGER_EXIT ; 
 int /*<<< orphan*/  MANAGER_HALT ; 
 int /*<<< orphan*/  MANAGER_KEXEC ; 
 int /*<<< orphan*/  MANAGER_POWEROFF ; 
 int /*<<< orphan*/  MANAGER_REBOOT ; 
 size_t _EXEC_DIRECTORY_TYPE_MAX ; 
 size_t _UNIT_TYPE_MAX ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bus_done (TYPE_1__*) ; 
 int /*<<< orphan*/  dynamic_user_vacuum (TYPE_1__*,int) ; 
 int /*<<< orphan*/  exec_runtime_vacuum (TYPE_1__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hashmap_isempty (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookup_paths_flush_generator (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lookup_paths_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  manager_clear_jobs_and_units (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_close_ask_password (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_close_idle_pipe (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_free_unit_name_maps (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_shutdown_cgroup (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* mfree (TYPE_1__*) ; 
 int /*<<< orphan*/  prioq_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rlimit_free_all (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safe_close_pair (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strv_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 TYPE_2__** unit_vtable ; 

Manager* manager_free(Manager *m) {
        ExecDirectoryType dt;
        UnitType c;

        if (!m)
                return NULL;

        manager_clear_jobs_and_units(m);

        for (c = 0; c < _UNIT_TYPE_MAX; c++)
                if (unit_vtable[c]->shutdown)
                        unit_vtable[c]->shutdown(m);

        /* Keep the cgroup hierarchy in place except when we know we are going down for good */
        manager_shutdown_cgroup(m, IN_SET(m->objective, MANAGER_EXIT, MANAGER_REBOOT, MANAGER_POWEROFF, MANAGER_HALT, MANAGER_KEXEC));

        lookup_paths_flush_generator(&m->lookup_paths);

        bus_done(m);

        exec_runtime_vacuum(m);
        hashmap_free(m->exec_runtime_by_id);

        dynamic_user_vacuum(m, false);
        hashmap_free(m->dynamic_users);

        hashmap_free(m->units);
        hashmap_free(m->units_by_invocation_id);
        hashmap_free(m->jobs);
        hashmap_free(m->watch_pids);
        hashmap_free(m->watch_bus);

        prioq_free(m->run_queue);

        set_free(m->startup_units);
        set_free(m->failed_units);

        sd_event_source_unref(m->signal_event_source);
        sd_event_source_unref(m->sigchld_event_source);
        sd_event_source_unref(m->notify_event_source);
        sd_event_source_unref(m->cgroups_agent_event_source);
        sd_event_source_unref(m->time_change_event_source);
        sd_event_source_unref(m->timezone_change_event_source);
        sd_event_source_unref(m->jobs_in_progress_event_source);
        sd_event_source_unref(m->run_queue_event_source);
        sd_event_source_unref(m->user_lookup_event_source);
        sd_event_source_unref(m->sync_bus_names_event_source);

        safe_close(m->signal_fd);
        safe_close(m->notify_fd);
        safe_close(m->cgroups_agent_fd);
        safe_close(m->time_change_fd);
        safe_close_pair(m->user_lookup_fds);

        manager_close_ask_password(m);

        manager_close_idle_pipe(m);

        sd_event_unref(m->event);

        free(m->notify_socket);

        lookup_paths_free(&m->lookup_paths);
        strv_free(m->transient_environment);
        strv_free(m->client_environment);

        hashmap_free(m->cgroup_unit);
        manager_free_unit_name_maps(m);

        free(m->switch_root);
        free(m->switch_root_init);

        rlimit_free_all(m->rlimit);

        assert(hashmap_isempty(m->units_requiring_mounts_for));
        hashmap_free(m->units_requiring_mounts_for);

        hashmap_free(m->uid_refs);
        hashmap_free(m->gid_refs);

        for (dt = 0; dt < _EXEC_DIRECTORY_TYPE_MAX; dt++)
                m->prefix[dt] = mfree(m->prefix[dt]);

        return mfree(m);
}