#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint64_t ;
struct TYPE_8__ {int /*<<< orphan*/  path; } ;
struct TYPE_7__ {int /*<<< orphan*/  path; } ;
struct TYPE_9__ {int /*<<< orphan*/  mmap; TYPE_2__ system_storage; TYPE_1__ runtime_storage; int /*<<< orphan*/  hostname_field; int /*<<< orphan*/  cgroup_root; int /*<<< orphan*/  tty_path; int /*<<< orphan*/  buffer; scalar_t__ kernel_seqnum; scalar_t__ ratelimit; int /*<<< orphan*/  notify_fd; int /*<<< orphan*/  hostname_fd; int /*<<< orphan*/  audit_fd; int /*<<< orphan*/  dev_kmsg_fd; int /*<<< orphan*/  stdout_fd; int /*<<< orphan*/  native_fd; int /*<<< orphan*/  syslog_fd; int /*<<< orphan*/  event; int /*<<< orphan*/  watchdog_event_source; int /*<<< orphan*/  notify_event_source; int /*<<< orphan*/  hostname_event_source; int /*<<< orphan*/  sigrtmin1_event_source; int /*<<< orphan*/  sigint_event_source; int /*<<< orphan*/  sigterm_event_source; int /*<<< orphan*/  sigusr2_event_source; int /*<<< orphan*/  sigusr1_event_source; int /*<<< orphan*/  sync_event_source; int /*<<< orphan*/  audit_event_source; int /*<<< orphan*/  dev_kmsg_event_source; int /*<<< orphan*/  stdout_event_source; int /*<<< orphan*/  native_event_source; int /*<<< orphan*/  syslog_event_source; int /*<<< orphan*/  varlink_server; int /*<<< orphan*/  user_journals; int /*<<< orphan*/  runtime_journal; int /*<<< orphan*/  system_journal; scalar_t__ stdout_streams; int /*<<< orphan*/  deferred_closes; } ;
typedef  TYPE_3__ Server ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_3__*) ; 
 int /*<<< orphan*/  client_context_flush_all (TYPE_3__*) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  journal_file_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  journal_ratelimit_free (scalar_t__) ; 
 int /*<<< orphan*/  mmap_cache_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  munmap (scalar_t__,int) ; 
 int /*<<< orphan*/  ordered_hashmap_free_with_destructor (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_unref (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_free_with_destructor (int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ )) ; 
 int /*<<< orphan*/  stdout_stream_free (scalar_t__) ; 
 int /*<<< orphan*/  varlink_server_unref (int /*<<< orphan*/ ) ; 

void server_done(Server *s) {
        assert(s);

        set_free_with_destructor(s->deferred_closes, journal_file_close);

        while (s->stdout_streams)
                stdout_stream_free(s->stdout_streams);

        client_context_flush_all(s);

        (void) journal_file_close(s->system_journal);
        (void) journal_file_close(s->runtime_journal);

        ordered_hashmap_free_with_destructor(s->user_journals, journal_file_close);

        varlink_server_unref(s->varlink_server);

        sd_event_source_unref(s->syslog_event_source);
        sd_event_source_unref(s->native_event_source);
        sd_event_source_unref(s->stdout_event_source);
        sd_event_source_unref(s->dev_kmsg_event_source);
        sd_event_source_unref(s->audit_event_source);
        sd_event_source_unref(s->sync_event_source);
        sd_event_source_unref(s->sigusr1_event_source);
        sd_event_source_unref(s->sigusr2_event_source);
        sd_event_source_unref(s->sigterm_event_source);
        sd_event_source_unref(s->sigint_event_source);
        sd_event_source_unref(s->sigrtmin1_event_source);
        sd_event_source_unref(s->hostname_event_source);
        sd_event_source_unref(s->notify_event_source);
        sd_event_source_unref(s->watchdog_event_source);
        sd_event_unref(s->event);

        safe_close(s->syslog_fd);
        safe_close(s->native_fd);
        safe_close(s->stdout_fd);
        safe_close(s->dev_kmsg_fd);
        safe_close(s->audit_fd);
        safe_close(s->hostname_fd);
        safe_close(s->notify_fd);

        if (s->ratelimit)
                journal_ratelimit_free(s->ratelimit);

        if (s->kernel_seqnum)
                munmap(s->kernel_seqnum, sizeof(uint64_t));

        free(s->buffer);
        free(s->tty_path);
        free(s->cgroup_root);
        free(s->hostname_field);
        free(s->runtime_storage.path);
        free(s->system_storage.path);

        mmap_cache_unref(s->mmap);
}