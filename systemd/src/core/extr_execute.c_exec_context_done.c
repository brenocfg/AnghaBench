#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int log_level_max; void* network_namespace_path; scalar_t__ stdin_data_size; void* stdin_data; scalar_t__ log_ratelimit_burst; scalar_t__ log_ratelimit_interval_usec; TYPE_1__* directories; void* address_families; void* syscall_archs; int /*<<< orphan*/  syscall_filter; void* smack_process_label; void* apparmor_profile; void* selinux_context; void* utmp_id; int /*<<< orphan*/  numa_policy; int /*<<< orphan*/  cpu_set; scalar_t__ n_temporary_filesystems; int /*<<< orphan*/ * temporary_filesystems; scalar_t__ n_bind_mounts; int /*<<< orphan*/ * bind_mounts; void* inaccessible_paths; void* read_write_paths; void* read_only_paths; void* pam_name; void* supplementary_groups; void* group; void* user; void* syslog_identifier; void* tty_path; void* root_image; void* root_directory; void* working_directory; void** stdio_file; void** stdio_fdname; int /*<<< orphan*/  rlimit; void* unset_environment; void* pass_environment; void* environment_files; void* environment; } ;
struct TYPE_6__ {void* paths; } ;
typedef  size_t ExecDirectoryType ;
typedef  TYPE_2__ ExecContext ;

/* Variables and functions */
 size_t _EXEC_DIRECTORY_TYPE_MAX ; 
 int /*<<< orphan*/  assert (TYPE_2__*) ; 
 int /*<<< orphan*/  bind_mount_free_many (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  cpu_set_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exec_context_free_log_extra_fields (TYPE_2__*) ; 
 int /*<<< orphan*/  hashmap_free (int /*<<< orphan*/ ) ; 
 void* mfree (void*) ; 
 int /*<<< orphan*/  numa_policy_reset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rlimit_free_all (int /*<<< orphan*/ ) ; 
 void* set_free (void*) ; 
 void* strv_free (void*) ; 
 int /*<<< orphan*/  temporary_filesystem_free_many (int /*<<< orphan*/ *,scalar_t__) ; 

void exec_context_done(ExecContext *c) {
        ExecDirectoryType i;
        size_t l;

        assert(c);

        c->environment = strv_free(c->environment);
        c->environment_files = strv_free(c->environment_files);
        c->pass_environment = strv_free(c->pass_environment);
        c->unset_environment = strv_free(c->unset_environment);

        rlimit_free_all(c->rlimit);

        for (l = 0; l < 3; l++) {
                c->stdio_fdname[l] = mfree(c->stdio_fdname[l]);
                c->stdio_file[l] = mfree(c->stdio_file[l]);
        }

        c->working_directory = mfree(c->working_directory);
        c->root_directory = mfree(c->root_directory);
        c->root_image = mfree(c->root_image);
        c->tty_path = mfree(c->tty_path);
        c->syslog_identifier = mfree(c->syslog_identifier);
        c->user = mfree(c->user);
        c->group = mfree(c->group);

        c->supplementary_groups = strv_free(c->supplementary_groups);

        c->pam_name = mfree(c->pam_name);

        c->read_only_paths = strv_free(c->read_only_paths);
        c->read_write_paths = strv_free(c->read_write_paths);
        c->inaccessible_paths = strv_free(c->inaccessible_paths);

        bind_mount_free_many(c->bind_mounts, c->n_bind_mounts);
        c->bind_mounts = NULL;
        c->n_bind_mounts = 0;
        temporary_filesystem_free_many(c->temporary_filesystems, c->n_temporary_filesystems);
        c->temporary_filesystems = NULL;
        c->n_temporary_filesystems = 0;

        cpu_set_reset(&c->cpu_set);
        numa_policy_reset(&c->numa_policy);

        c->utmp_id = mfree(c->utmp_id);
        c->selinux_context = mfree(c->selinux_context);
        c->apparmor_profile = mfree(c->apparmor_profile);
        c->smack_process_label = mfree(c->smack_process_label);

        c->syscall_filter = hashmap_free(c->syscall_filter);
        c->syscall_archs = set_free(c->syscall_archs);
        c->address_families = set_free(c->address_families);

        for (i = 0; i < _EXEC_DIRECTORY_TYPE_MAX; i++)
                c->directories[i].paths = strv_free(c->directories[i].paths);

        c->log_level_max = -1;

        exec_context_free_log_extra_fields(c);

        c->log_ratelimit_interval_usec = 0;
        c->log_ratelimit_burst = 0;

        c->stdin_data = mfree(c->stdin_data);
        c->stdin_data_size = 0;

        c->network_namespace_path = mfree(c->network_namespace_path);
}