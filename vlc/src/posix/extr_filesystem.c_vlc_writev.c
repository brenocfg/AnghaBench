#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct timespec {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct iovec {int dummy; } ;
typedef  scalar_t__ ssize_t ;
typedef  int /*<<< orphan*/  sigset_t ;
typedef  int /*<<< orphan*/  siginfo_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EPIPE ; 
 int SIGPIPE ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  pthread_sigmask (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigaddset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigismember (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sigpending (int /*<<< orphan*/ *) ; 
 scalar_t__ sigtimedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,struct timespec*) ; 
 int /*<<< orphan*/  sigwait (int /*<<< orphan*/ *,int*) ; 
 scalar_t__ writev (int,struct iovec const*,int) ; 

ssize_t vlc_writev(int fd, const struct iovec *iov, int count)
{
    sigset_t set, oset;

    sigemptyset(&set);
    sigaddset(&set, SIGPIPE);
    pthread_sigmask(SIG_BLOCK, &set, &oset);

    ssize_t val = writev(fd, iov, count);
    if (val < 0 && errno == EPIPE)
    {
#if (_POSIX_REALTIME_SIGNALS > 0)
        siginfo_t info;
        struct timespec ts = { 0, 0 };

        while (sigtimedwait(&set, &info, &ts) >= 0 || errno != EAGAIN);
#else
        for (;;)
        {
            sigset_t s;
            int num;

            sigpending(&s);
            if (!sigismember(&s, SIGPIPE))
                break;

            sigwait(&set, &num);
            assert(num == SIGPIPE);
        }
#endif
    }

    if (!sigismember(&oset, SIGPIPE)) /* Restore the signal mask if changed */
        pthread_sigmask(SIG_SETMASK, &oset, NULL);
    return val;
}