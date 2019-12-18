#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ result; int will_auto_restart; int flush_n_restarts; int forbid_restart; int /*<<< orphan*/  exec_context; scalar_t__ pid_file; int /*<<< orphan*/  dynamic_creds; int /*<<< orphan*/  exec_runtime; int /*<<< orphan*/  n_keep_fd_store; int /*<<< orphan*/  restart_usec; } ;
typedef  int /*<<< orphan*/  ServiceState ;
typedef  scalar_t__ ServiceResult ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  SERVICE_AUTO_RESTART ; 
 int /*<<< orphan*/  SERVICE_DEAD ; 
 int /*<<< orphan*/  SERVICE_FAILED ; 
 scalar_t__ SERVICE_FAILURE_RESOURCES ; 
 scalar_t__ SERVICE_SKIP_CONDITION ; 
 scalar_t__ SERVICE_SUCCESS ; 
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  dynamic_creds_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exec_context_revert_tty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  exec_runtime_unref (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  log_unit_debug (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  log_unit_warning_errno (int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  now (int /*<<< orphan*/ ) ; 
 int service_arm_timer (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_result_to_string (scalar_t__) ; 
 int /*<<< orphan*/  service_set_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int service_shall_restart (TYPE_1__*,char const**) ; 
 int /*<<< orphan*/  unit_add_to_gc_queue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_destroy_runtime_directory (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unit_log_failure (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_log_skip (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_log_success (int /*<<< orphan*/ ) ; 
 scalar_t__ unit_stop_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  unit_unref_uid_gid (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  unlink (scalar_t__) ; 
 int /*<<< orphan*/  usec_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void service_enter_dead(Service *s, ServiceResult f, bool allow_restart) {
        ServiceState end_state;
        int r;

        assert(s);

        /* If there's a stop job queued before we enter the DEAD state, we shouldn't act on Restart=, in order to not
         * undo what has already been enqueued. */
        if (unit_stop_pending(UNIT(s)))
                allow_restart = false;

        if (s->result == SERVICE_SUCCESS)
                s->result = f;

        if (s->result == SERVICE_SUCCESS) {
                unit_log_success(UNIT(s));
                end_state = SERVICE_DEAD;
        } else if (s->result == SERVICE_SKIP_CONDITION) {
                unit_log_skip(UNIT(s), service_result_to_string(s->result));
                end_state = SERVICE_DEAD;
        } else {
                unit_log_failure(UNIT(s), service_result_to_string(s->result));
                end_state = SERVICE_FAILED;
        }

        if (!allow_restart)
                log_unit_debug(UNIT(s), "Service restart not allowed.");
        else {
                const char *reason;
                bool shall_restart;

                shall_restart = service_shall_restart(s, &reason);
                log_unit_debug(UNIT(s), "Service will %srestart (%s)",
                                        shall_restart ? "" : "not ",
                                        reason);
                if (shall_restart)
                        s->will_auto_restart = true;
        }

        /* Make sure service_release_resources() doesn't destroy our FD store, while we are changing through
         * SERVICE_FAILED/SERVICE_DEAD before entering into SERVICE_AUTO_RESTART. */
        s->n_keep_fd_store ++;

        service_set_state(s, end_state);

        if (s->will_auto_restart) {
                s->will_auto_restart = false;

                r = service_arm_timer(s, usec_add(now(CLOCK_MONOTONIC), s->restart_usec));
                if (r < 0) {
                        s->n_keep_fd_store--;
                        goto fail;
                }

                service_set_state(s, SERVICE_AUTO_RESTART);
        } else
                /* If we shan't restart, then flush out the restart counter. But don't do that immediately, so that the
                 * user can still introspect the counter. Do so on the next start. */
                s->flush_n_restarts = true;

        /* The new state is in effect, let's decrease the fd store ref counter again. Let's also re-add us to the GC
         * queue, so that the fd store is possibly gc'ed again */
        s->n_keep_fd_store--;
        unit_add_to_gc_queue(UNIT(s));

        /* The next restart might not be a manual stop, hence reset the flag indicating manual stops */
        s->forbid_restart = false;

        /* We want fresh tmpdirs in case service is started again immediately */
        s->exec_runtime = exec_runtime_unref(s->exec_runtime, true);

        /* Also, remove the runtime directory */
        unit_destroy_runtime_directory(UNIT(s), &s->exec_context);

        /* Get rid of the IPC bits of the user */
        unit_unref_uid_gid(UNIT(s), true);

        /* Release the user, and destroy it if we are the only remaining owner */
        dynamic_creds_destroy(&s->dynamic_creds);

        /* Try to delete the pid file. At this point it will be
         * out-of-date, and some software might be confused by it, so
         * let's remove it. */
        if (s->pid_file)
                (void) unlink(s->pid_file);

        /* Reset TTY ownership if necessary */
        exec_context_revert_tty(&s->exec_context);

        return;

fail:
        log_unit_warning_errno(UNIT(s), r, "Failed to run install restart timer: %m");
        service_enter_dead(s, SERVICE_FAILURE_RESOURCES, false);
}