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
typedef  int /*<<< orphan*/  vlc_interrupt_t ;
typedef  int /*<<< orphan*/  uint64_t ;
struct pollfd {int fd; scalar_t__ revents; int /*<<< orphan*/  events; } ;
typedef  int /*<<< orphan*/  dummy ;

/* Variables and functions */
 int /*<<< orphan*/  EFD_CLOEXEC ; 
 int /*<<< orphan*/  EINTR ; 
 int /*<<< orphan*/  ENOMEM ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  errno ; 
 int eventfd (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int poll (struct pollfd*,unsigned int,int) ; 
 int /*<<< orphan*/  read (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cleanup_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_close (int) ; 
 scalar_t__ vlc_interrupt_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int*) ; 
 scalar_t__ vlc_pipe (int*) ; 
 int /*<<< orphan*/  vlc_poll_i11e_cleanup ; 
 int /*<<< orphan*/  vlc_poll_i11e_wake ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 int /*<<< orphan*/  vlc_testcancel () ; 

__attribute__((used)) static int vlc_poll_i11e_inner(struct pollfd *restrict fds, unsigned nfds,
                               int timeout, vlc_interrupt_t *ctx,
                               struct pollfd *restrict ufd)
{
    int fd[2];
    int ret = -1;
    int canc;

    /* TODO: cache this */
# if defined (HAVE_EVENTFD) && defined (EFD_CLOEXEC)
    canc = vlc_savecancel();
    fd[0] = eventfd(0, EFD_CLOEXEC);
    vlc_restorecancel(canc);
    if (fd[0] != -1)
        fd[1] = fd[0];
    else
# endif
    if (vlc_pipe(fd))
    {
        vlc_testcancel();
        errno = ENOMEM;
        return -1;
    }

    for (unsigned i = 0; i < nfds; i++)
    {
        ufd[i].fd = fds[i].fd;
        ufd[i].events = fds[i].events;
    }
    ufd[nfds].fd = fd[0];
    ufd[nfds].events = POLLIN;

    vlc_interrupt_prepare(ctx, vlc_poll_i11e_wake, fd);

    vlc_cleanup_push(vlc_poll_i11e_cleanup, ctx);
    ret = poll(ufd, nfds + 1, timeout);

    for (unsigned i = 0; i < nfds; i++)
        fds[i].revents = ufd[i].revents;

    if (ret > 0 && ufd[nfds].revents)
    {
        uint64_t dummy;

        read(fd[0], &dummy, sizeof (dummy));
        ret--;
    }
    vlc_cleanup_pop();

    if (vlc_interrupt_finish(ctx))
    {
        errno = EINTR;
        ret = -1;
    }

    canc = vlc_savecancel();
    if (fd[1] != fd[0])
        vlc_close(fd[1]);
    vlc_close(fd[0]);
    vlc_restorecancel(canc);
    return ret;
}