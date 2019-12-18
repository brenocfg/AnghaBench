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
typedef  scalar_t__ usec_t ;
struct timespec {int dummy; } ;
typedef  int /*<<< orphan*/  sigset_t ;
struct TYPE_5__ {scalar_t__ si_pid; scalar_t__ si_code; int si_status; scalar_t__ si_signo; } ;
typedef  TYPE_1__ siginfo_t ;
typedef  int /*<<< orphan*/  sd_id128_t ;
typedef  scalar_t__ pid_t ;
typedef  int /*<<< orphan*/  new_environment ;

/* Variables and functions */
 scalar_t__ CLD_EXITED ; 
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 scalar_t__ DEFAULT_TIMEOUT_USEC ; 
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ ENOTTY ; 
 int ESRCH ; 
 int EXIT_EXCEPTION ; 
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  P_ALL ; 
 int /*<<< orphan*/  RB_AUTOBOOT ; 
 int /*<<< orphan*/  RB_POWER_OFF ; 
 int SD_ID128_STRING_MAX ; 
 scalar_t__ SIGCHLD ; 
 int /*<<< orphan*/  SIGHUP ; 
 scalar_t__ SIGINT ; 
 scalar_t__ SIGRTMIN ; 
 int /*<<< orphan*/  SIGTERM ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  STDIN_FILENO ; 
 int /*<<< orphan*/  TIOCNOTTY ; 
 scalar_t__ USEC_INFINITY ; 
 int WEXITED ; 
 int WNOHANG ; 
 int /*<<< orphan*/  _exit (int) ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  close_all_fds (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ errno ; 
 scalar_t__ fork () ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kill (scalar_t__,int /*<<< orphan*/ ) ; 
 int kill_and_sigcont (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_close () ; 
 int log_error_errno (scalar_t__,char*) ; 
 int /*<<< orphan*/  log_open () ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reboot (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rename_process (char*) ; 
 int /*<<< orphan*/  reset_all_signal_handlers () ; 
 int /*<<< orphan*/  reset_environ (char*,int) ; 
 int /*<<< orphan*/  sd_id128_to_string (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  setsid () ; 
 scalar_t__ sigemptyset (int /*<<< orphan*/ *) ; 
 scalar_t__ sigfillset (int /*<<< orphan*/ *) ; 
 scalar_t__ sigprocmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sigset_add_many (int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 
 int sigtimedwait (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int sigwaitinfo (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  timespec_store (struct timespec*,scalar_t__) ; 
 int waitid (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int) ; 

int stub_pid1(sd_id128_t uuid) {
        enum {
                STATE_RUNNING,
                STATE_REBOOT,
                STATE_POWEROFF,
        } state = STATE_RUNNING;

        sigset_t fullmask, oldmask, waitmask;
        usec_t quit_usec = USEC_INFINITY;
        pid_t pid;
        int r;

        /* The new environment we set up, on the stack. */
        char new_environment[] =
                "container=systemd-nspawn\0"
                "container_uuid=XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

        /* Implements a stub PID 1, that reaps all processes and processes a couple of standard signals. This is useful
         * for allowing arbitrary processes run in a container, and still have all zombies reaped. */

        assert_se(sigfillset(&fullmask) >= 0);
        assert_se(sigprocmask(SIG_BLOCK, &fullmask, &oldmask) >= 0);

        /* Surrender the terminal this stub may control so that child processes can have a controlling terminal
         * without resorting to setsid hacks. */
        r = ioctl(STDIN_FILENO, TIOCNOTTY);
        if (r < 0 && errno != ENOTTY)
                return log_error_errno(errno, "Failed to surrender controlling terminal: %m");

        pid = fork();
        if (pid < 0)
                return log_error_errno(errno, "Failed to fork child pid: %m");

        if (pid == 0) {
                /* Return in the child */
                assert_se(sigprocmask(SIG_SETMASK, &oldmask, NULL) >= 0);
                setsid();
                return 0;
        }

        reset_all_signal_handlers();

        log_close();
        (void) close_all_fds(NULL, 0);
        log_open();

        /* Flush out /proc/self/environ, so that we don't leak the environment from the host into the container. Also,
         * set $container= and $container_uuid= so that clients in the container that query it from /proc/1/environ
         * find them set. */
        sd_id128_to_string(uuid, new_environment + sizeof(new_environment) - SD_ID128_STRING_MAX);
        reset_environ(new_environment, sizeof(new_environment));

        (void) rename_process("(sd-stubinit)");

        assert_se(sigemptyset(&waitmask) >= 0);
        assert_se(sigset_add_many(&waitmask,
                                  SIGCHLD,          /* posix: process died */
                                  SIGINT,           /* sysv: ctrl-alt-del */
                                  SIGRTMIN+3,       /* systemd: halt */
                                  SIGRTMIN+4,       /* systemd: poweroff */
                                  SIGRTMIN+5,       /* systemd: reboot */
                                  SIGRTMIN+6,       /* systemd: kexec */
                                  SIGRTMIN+13,      /* systemd: halt */
                                  SIGRTMIN+14,      /* systemd: poweroff */
                                  SIGRTMIN+15,      /* systemd: reboot */
                                  SIGRTMIN+16,      /* systemd: kexec */
                                  -1) >= 0);

        /* Note that we ignore SIGTERM (sysv's reexec), SIGHUP (reload), and all other signals here, since we don't
         * support reexec/reloading in this stub process. */

        for (;;) {
                siginfo_t si;
                usec_t current_usec;

                si.si_pid = 0;
                r = waitid(P_ALL, 0, &si, WEXITED|WNOHANG);
                if (r < 0) {
                        r = log_error_errno(errno, "Failed to reap children: %m");
                        goto finish;
                }

                current_usec = now(CLOCK_MONOTONIC);

                if (si.si_pid == pid || current_usec >= quit_usec) {

                        /* The child we started ourselves died or we reached a timeout. */

                        if (state == STATE_REBOOT) { /* dispatch a queued reboot */
                                (void) reboot(RB_AUTOBOOT);
                                r = log_error_errno(errno, "Failed to reboot: %m");
                                goto finish;

                        } else if (state == STATE_POWEROFF)
                                (void) reboot(RB_POWER_OFF); /* if this fails, fall back to normal exit. */

                        if (si.si_pid == pid && si.si_code == CLD_EXITED)
                                r = si.si_status; /* pass on exit code */
                        else
                                r = EXIT_EXCEPTION; /* signal, coredump, timeout, … */

                        goto finish;
                }
                if (si.si_pid != 0)
                        /* We reaped something. Retry until there's nothing more to reap. */
                        continue;

                if (quit_usec == USEC_INFINITY)
                        r = sigwaitinfo(&waitmask, &si);
                else {
                        struct timespec ts;
                        r = sigtimedwait(&waitmask, &si, timespec_store(&ts, quit_usec - current_usec));
                }
                if (r < 0) {
                        if (errno == EINTR) /* strace -p attach can result in EINTR, let's handle this nicely. */
                                continue;
                        if (errno == EAGAIN) /* timeout reached */
                                continue;

                        r = log_error_errno(errno, "Failed to wait for signal: %m");
                        goto finish;
                }

                if (si.si_signo == SIGCHLD)
                        continue; /* Let's reap this */

                if (state != STATE_RUNNING)
                        continue;

                /* Would love to use a switch() statement here, but SIGRTMIN is actually a function call, not a
                 * constant… */

                if (si.si_signo == SIGRTMIN+3 ||
                    si.si_signo == SIGRTMIN+4 ||
                    si.si_signo == SIGRTMIN+13 ||
                    si.si_signo == SIGRTMIN+14)

                        state = STATE_POWEROFF;

                else if (si.si_signo == SIGINT ||
                         si.si_signo == SIGRTMIN+5 ||
                         si.si_signo == SIGRTMIN+6 ||
                         si.si_signo == SIGRTMIN+15 ||
                         si.si_signo == SIGRTMIN+16)

                        state = STATE_REBOOT;
                else
                        assert_not_reached("Got unexpected signal");

                r = kill_and_sigcont(pid, SIGTERM);

                /* Let's send a SIGHUP after the SIGTERM, as shells tend to ignore SIGTERM but do react to SIGHUP. We
                 * do it strictly in this order, so that the SIGTERM is dispatched first, and SIGHUP second for those
                 * processes which handle both. That's because services tend to bind configuration reload or something
                 * else to SIGHUP. */

                if (r != -ESRCH)
                        (void) kill(pid, SIGHUP);

                quit_usec = now(CLOCK_MONOTONIC) + DEFAULT_TIMEOUT_USEC;
        }

finish:
        _exit(r < 0 ? EXIT_FAILURE : r);
}