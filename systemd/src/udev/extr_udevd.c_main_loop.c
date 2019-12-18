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
struct TYPE_8__ {int* worker_watch; int fd_inotify; int /*<<< orphan*/  event; int /*<<< orphan*/  rules; int /*<<< orphan*/  monitor; int /*<<< orphan*/  inotify_event; int /*<<< orphan*/  ctrl; int /*<<< orphan*/  pid; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  AF_LOCAL ; 
 int /*<<< orphan*/  EPOLLIN ; 
 size_t READ_END ; 
 int /*<<< orphan*/  SD_EVENT_PRIORITY_IDLE ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int SOCK_CLOEXEC ; 
 int SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_PASSCRED ; 
 int /*<<< orphan*/  arg_children_max ; 
 int /*<<< orphan*/  arg_resolve_name_timing ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int errno ; 
 int /*<<< orphan*/  getpid_cached () ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  on_ctrl_msg ; 
 int /*<<< orphan*/  on_inotify ; 
 int /*<<< orphan*/  on_post ; 
 int /*<<< orphan*/  on_sigchld ; 
 int /*<<< orphan*/  on_sighup ; 
 int /*<<< orphan*/  on_sigterm ; 
 int /*<<< orphan*/  on_uevent ; 
 int /*<<< orphan*/  on_worker ; 
 int sd_device_monitor_attach_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_device_monitor_get_event_source (int /*<<< orphan*/ ) ; 
 int sd_device_monitor_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sd_event_add_io (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sd_event_add_post (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sd_event_add_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sd_event_default (int /*<<< orphan*/ *) ; 
 int sd_event_loop (int /*<<< orphan*/ ) ; 
 int sd_event_set_watchdog (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sd_event_source_set_description (int /*<<< orphan*/ ,char*) ; 
 int sd_event_source_set_priority (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_notify (int,char*) ; 
 int /*<<< orphan*/  sd_notifyf (int,char*,int /*<<< orphan*/ ) ; 
 int setsockopt_int (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ sigprocmask_many (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int socketpair (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  udev_builtin_init () ; 
 int udev_ctrl_attach_event (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_ctrl_get_event_source (int /*<<< orphan*/ ) ; 
 int udev_ctrl_start (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int udev_rules_apply_static_dev_perms (int /*<<< orphan*/ ) ; 
 int udev_rules_new (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int udev_watch_init () ; 
 int /*<<< orphan*/  udev_watch_restore () ; 

__attribute__((used)) static int main_loop(Manager *manager) {
        int fd_worker, r;

        manager->pid = getpid_cached();

        /* unnamed socket from workers to the main daemon */
        r = socketpair(AF_LOCAL, SOCK_DGRAM|SOCK_CLOEXEC, 0, manager->worker_watch);
        if (r < 0)
                return log_error_errno(errno, "Failed to create socketpair for communicating with workers: %m");

        fd_worker = manager->worker_watch[READ_END];

        r = setsockopt_int(fd_worker, SOL_SOCKET, SO_PASSCRED, true);
        if (r < 0)
                return log_error_errno(r, "Failed to enable SO_PASSCRED: %m");

        r = udev_watch_init();
        if (r < 0)
                return log_error_errno(r, "Failed to create inotify descriptor: %m");
        manager->fd_inotify = r;

        udev_watch_restore();

        /* block and listen to all signals on signalfd */
        assert_se(sigprocmask_many(SIG_BLOCK, NULL, SIGTERM, SIGINT, SIGHUP, SIGCHLD, -1) >= 0);

        r = sd_event_default(&manager->event);
        if (r < 0)
                return log_error_errno(r, "Failed to allocate event loop: %m");

        r = sd_event_add_signal(manager->event, NULL, SIGINT, on_sigterm, manager);
        if (r < 0)
                return log_error_errno(r, "Failed to create SIGINT event source: %m");

        r = sd_event_add_signal(manager->event, NULL, SIGTERM, on_sigterm, manager);
        if (r < 0)
                return log_error_errno(r, "Failed to create SIGTERM event source: %m");

        r = sd_event_add_signal(manager->event, NULL, SIGHUP, on_sighup, manager);
        if (r < 0)
                return log_error_errno(r, "Failed to create SIGHUP event source: %m");

        r = sd_event_add_signal(manager->event, NULL, SIGCHLD, on_sigchld, manager);
        if (r < 0)
                return log_error_errno(r, "Failed to create SIGCHLD event source: %m");

        r = sd_event_set_watchdog(manager->event, true);
        if (r < 0)
                return log_error_errno(r, "Failed to create watchdog event source: %m");

        r = udev_ctrl_attach_event(manager->ctrl, manager->event);
        if (r < 0)
                return log_error_errno(r, "Failed to attach event to udev control: %m");

        r = udev_ctrl_start(manager->ctrl, on_ctrl_msg, manager);
        if (r < 0)
                return log_error_errno(r, "Failed to start device monitor: %m");

        /* This needs to be after the inotify and uevent handling, to make sure
         * that the ping is send back after fully processing the pending uevents
         * (including the synthetic ones we may create due to inotify events).
         */
        r = sd_event_source_set_priority(udev_ctrl_get_event_source(manager->ctrl), SD_EVENT_PRIORITY_IDLE);
        if (r < 0)
                return log_error_errno(r, "Failed to set IDLE event priority for udev control event source: %m");

        r = sd_event_add_io(manager->event, &manager->inotify_event, manager->fd_inotify, EPOLLIN, on_inotify, manager);
        if (r < 0)
                return log_error_errno(r, "Failed to create inotify event source: %m");

        r = sd_device_monitor_attach_event(manager->monitor, manager->event);
        if (r < 0)
                return log_error_errno(r, "Failed to attach event to device monitor: %m");

        r = sd_device_monitor_start(manager->monitor, on_uevent, manager);
        if (r < 0)
                return log_error_errno(r, "Failed to start device monitor: %m");

        (void) sd_event_source_set_description(sd_device_monitor_get_event_source(manager->monitor), "device-monitor");

        r = sd_event_add_io(manager->event, NULL, fd_worker, EPOLLIN, on_worker, manager);
        if (r < 0)
                return log_error_errno(r, "Failed to create worker event source: %m");

        r = sd_event_add_post(manager->event, NULL, on_post, manager);
        if (r < 0)
                return log_error_errno(r, "Failed to create post event source: %m");

        udev_builtin_init();

        r = udev_rules_new(&manager->rules, arg_resolve_name_timing);
        if (!manager->rules)
                return log_error_errno(r, "Failed to read udev rules: %m");

        r = udev_rules_apply_static_dev_perms(manager->rules);
        if (r < 0)
                log_error_errno(r, "Failed to apply permissions on static device nodes: %m");

        (void) sd_notifyf(false,
                          "READY=1\n"
                          "STATUS=Processing with %u children at max", arg_children_max);

        r = sd_event_loop(manager->event);
        if (r < 0)
                log_error_errno(r, "Event loop failed: %m");

        sd_notify(false,
                  "STOPPING=1\n"
                  "STATUS=Shutting down...");
        return r;
}