#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_5__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  path; } ;
struct TYPE_7__ {TYPE_5__* pid_file_pathspec; } ;
typedef  TYPE_1__ Service ;

/* Variables and functions */
 int /*<<< orphan*/  UNIT (TYPE_1__*) ; 
 int /*<<< orphan*/  log_unit_debug (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_unit_error_errno (int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ ) ; 
 int path_spec_watch (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  service_dispatch_inotify_io ; 
 int /*<<< orphan*/  service_retry_pid_file (TYPE_1__*) ; 
 int /*<<< orphan*/  service_unwatch_pid_file (TYPE_1__*) ; 

__attribute__((used)) static int service_watch_pid_file(Service *s) {
        int r;

        log_unit_debug(UNIT(s), "Setting watch for PID file %s", s->pid_file_pathspec->path);

        r = path_spec_watch(s->pid_file_pathspec, service_dispatch_inotify_io);
        if (r < 0)
                goto fail;

        /* the pidfile might have appeared just before we set the watch */
        log_unit_debug(UNIT(s), "Trying to read PID file %s in case it changed", s->pid_file_pathspec->path);
        service_retry_pid_file(s);

        return 0;
fail:
        log_unit_error_errno(UNIT(s), r, "Failed to set a watch for PID file %s: %m", s->pid_file_pathspec->path);
        service_unwatch_pid_file(s);
        return r;
}