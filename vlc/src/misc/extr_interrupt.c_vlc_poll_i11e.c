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
struct pollfd {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  free (struct pollfd*) ; 
 scalar_t__ likely (int) ; 
 int poll (struct pollfd*,unsigned int,int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 struct pollfd* vlc_alloc (unsigned int,int) ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cleanup_push (int /*<<< orphan*/  (*) (struct pollfd*),struct pollfd*) ; 
 int /*<<< orphan*/ * vlc_interrupt_var ; 
 int vlc_poll_i11e_inner (struct pollfd*,unsigned int,int,int /*<<< orphan*/ *,struct pollfd*) ; 

int vlc_poll_i11e(struct pollfd *fds, unsigned nfds, int timeout)
{
    vlc_interrupt_t *ctx = vlc_interrupt_var;
    if (ctx == NULL)
        return poll(fds, nfds, timeout);

    int ret;

    if (likely(nfds < 255))
    {   /* Fast path with stack allocation */
        struct pollfd ufd[nfds + 1];

        ret = vlc_poll_i11e_inner(fds, nfds, timeout, ctx, ufd);
    }
    else
    {   /* Slow path but poll() is slow with large nfds anyway. */
        struct pollfd *ufd = vlc_alloc(nfds + 1, sizeof (*ufd));
        if (unlikely(ufd == NULL))
            return -1; /* ENOMEM */

        vlc_cleanup_push(free, ufd);
        ret = vlc_poll_i11e_inner(fds, nfds, timeout, ctx, ufd);
        vlc_cleanup_pop();
        free(ufd);
    }
    return ret;
}