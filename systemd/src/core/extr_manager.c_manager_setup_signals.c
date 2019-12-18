#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct sigaction {int sa_flags; int /*<<< orphan*/  sa_handler; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_7__ {scalar_t__ signal_fd; int /*<<< orphan*/  signal_event_source; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  EPOLLIN ; 
 scalar_t__ MANAGER_IS_SYSTEM (TYPE_1__*) ; 
 int /*<<< orphan*/  RTSIG_IF_AVAILABLE (scalar_t__) ; 
 int SA_NOCLDSTOP ; 
 int SA_RESTART ; 
 scalar_t__ SD_EVENT_PRIORITY_NORMAL ; 
 int SFD_CLOEXEC ; 
 int SFD_NONBLOCK ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 int /*<<< orphan*/  SIGINT ; 
 int /*<<< orphan*/  SIGPWR ; 
 scalar_t__ SIGRTMIN ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIGUSR2 ; 
 int /*<<< orphan*/  SIGWINCH ; 
 int /*<<< orphan*/  SIG_DFL ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int enable_special_signals (TYPE_1__*) ; 
 int errno ; 
 int /*<<< orphan*/  manager_dispatch_signal_fd ; 
 int sd_event_add_io (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sd_event_source_set_description (int /*<<< orphan*/ ,char*) ; 
 int sd_event_source_set_priority (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sigaction (int /*<<< orphan*/ ,struct sigaction*,int /*<<< orphan*/ *) ; 
 scalar_t__ sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ signalfd (int,int /*<<< orphan*/ *,int) ; 
 scalar_t__ sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigset_add_many (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int manager_setup_signals(Manager *m) {
        struct sigaction sa = {
                .sa_handler = SIG_DFL,
                .sa_flags = SA_NOCLDSTOP|SA_RESTART,
        };
        sigset_t mask;
        int r;

        assert(m);

        assert_se(sigaction(SIGCHLD, &sa, NULL) == 0);

        /* We make liberal use of realtime signals here. On
         * Linux/glibc we have 30 of them (with the exception of Linux
         * on hppa, see below), between SIGRTMIN+0 ... SIGRTMIN+30
         * (aka SIGRTMAX). */

        assert_se(sigemptyset(&mask) == 0);
        sigset_add_many(&mask,
                        SIGCHLD,     /* Child died */
                        SIGTERM,     /* Reexecute daemon */
                        SIGHUP,      /* Reload configuration */
                        SIGUSR1,     /* systemd/upstart: reconnect to D-Bus */
                        SIGUSR2,     /* systemd: dump status */
                        SIGINT,      /* Kernel sends us this on control-alt-del */
                        SIGWINCH,    /* Kernel sends us this on kbrequest (alt-arrowup) */
                        SIGPWR,      /* Some kernel drivers and upsd send us this on power failure */

                        SIGRTMIN+0,  /* systemd: start default.target */
                        SIGRTMIN+1,  /* systemd: isolate rescue.target */
                        SIGRTMIN+2,  /* systemd: isolate emergency.target */
                        SIGRTMIN+3,  /* systemd: start halt.target */
                        SIGRTMIN+4,  /* systemd: start poweroff.target */
                        SIGRTMIN+5,  /* systemd: start reboot.target */
                        SIGRTMIN+6,  /* systemd: start kexec.target */

                        /* ... space for more special targets ... */

                        SIGRTMIN+13, /* systemd: Immediate halt */
                        SIGRTMIN+14, /* systemd: Immediate poweroff */
                        SIGRTMIN+15, /* systemd: Immediate reboot */
                        SIGRTMIN+16, /* systemd: Immediate kexec */

                        /* ... space for more immediate system state changes ... */

                        SIGRTMIN+20, /* systemd: enable status messages */
                        SIGRTMIN+21, /* systemd: disable status messages */
                        SIGRTMIN+22, /* systemd: set log level to LOG_DEBUG */
                        SIGRTMIN+23, /* systemd: set log level to LOG_INFO */
                        SIGRTMIN+24, /* systemd: Immediate exit (--user only) */

                        /* .. one free signal here ... */

                        /* Apparently Linux on hppa had fewer RT signals until v3.18,
                         * SIGRTMAX was SIGRTMIN+25, and then SIGRTMIN was lowered,
                         * see commit v3.17-7614-g1f25df2eff.
                         *
                         * We cannot unconditionally make use of those signals here,
                         * so let's use a runtime check. Since these commands are
                         * accessible by different means and only really a safety
                         * net, the missing functionality on hppa shouldn't matter.
                         */

                        RTSIG_IF_AVAILABLE(SIGRTMIN+26), /* systemd: set log target to journal-or-kmsg */
                        RTSIG_IF_AVAILABLE(SIGRTMIN+27), /* systemd: set log target to console */
                        RTSIG_IF_AVAILABLE(SIGRTMIN+28), /* systemd: set log target to kmsg */
                        RTSIG_IF_AVAILABLE(SIGRTMIN+29), /* systemd: set log target to syslog-or-kmsg (obsolete) */

                        /* ... one free signal here SIGRTMIN+30 ... */
                        -1);
        assert_se(sigprocmask(SIG_SETMASK, &mask, NULL) == 0);

        m->signal_fd = signalfd(-1, &mask, SFD_NONBLOCK|SFD_CLOEXEC);
        if (m->signal_fd < 0)
                return -errno;

        r = sd_event_add_io(m->event, &m->signal_event_source, m->signal_fd, EPOLLIN, manager_dispatch_signal_fd, m);
        if (r < 0)
                return r;

        (void) sd_event_source_set_description(m->signal_event_source, "manager-signal");

        /* Process signals a bit earlier than the rest of things, but later than notify_fd processing, so that the
         * notify processing can still figure out to which process/service a message belongs, before we reap the
         * process. Also, process this before handling cgroup notifications, so that we always collect child exit
         * status information before detecting that there's no process in a cgroup. */
        r = sd_event_source_set_priority(m->signal_event_source, SD_EVENT_PRIORITY_NORMAL-6);
        if (r < 0)
                return r;

        if (MANAGER_IS_SYSTEM(m))
                return enable_special_signals(m);

        return 0;
}