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
typedef  int /*<<< orphan*/  vlc_thread_t ;
typedef  int /*<<< orphan*/  vlc_interrupt_t ;

/* Variables and functions */
 int /*<<< orphan*/  PF_LOCAL ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  VLC_THREAD_PRIORITY_LOW ; 
 int /*<<< orphan*/  alarm (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * fds ; 
 int /*<<< orphan*/  sem ; 
 int /*<<< orphan*/  test_context_simple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_thread_cancel ; 
 int /*<<< orphan*/  test_thread_cleanup ; 
 int /*<<< orphan*/  test_thread_simple ; 
 int /*<<< orphan*/  unreachable_callback ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_clone (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_interrupt_create () ; 
 int /*<<< orphan*/  vlc_interrupt_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_forward_start (int /*<<< orphan*/ *,void**) ; 
 scalar_t__ vlc_interrupt_forward_stop (void**) ; 
 int /*<<< orphan*/  vlc_interrupt_raise (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_unregister () ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_mwait_i11e (int) ; 
 scalar_t__ vlc_poll_i11e (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_sem_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_sem_post (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_sem_wait_i11e (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_socketpair (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

int main (void)
{
    vlc_interrupt_t *ctx;
    vlc_thread_t th;

    alarm(2);

    ctx = vlc_interrupt_create();
    assert(ctx != NULL);
    vlc_interrupt_destroy(ctx);

    vlc_sem_init(&sem, 0);
    ctx = vlc_interrupt_create();
    assert(ctx != NULL);

    assert(vlc_socketpair(PF_LOCAL, SOCK_STREAM, 0, fds, false) == 0);

    test_context_simple(ctx);

    assert(!vlc_clone(&th, test_thread_simple, ctx, VLC_THREAD_PRIORITY_LOW));
    vlc_interrupt_raise(ctx);
    vlc_sem_post(&sem);
    vlc_sem_post(&sem);
    vlc_join(th, NULL);

    assert(!vlc_clone(&th, test_thread_cleanup, ctx, VLC_THREAD_PRIORITY_LOW));
    vlc_join(th, NULL);

    assert(!vlc_clone(&th, test_thread_cancel, ctx, VLC_THREAD_PRIORITY_LOW));
    vlc_cancel(th);
    vlc_join(th, NULL);

    vlc_interrupt_destroy(ctx);

    /* Tests without interrupt context */
    vlc_sem_post(&sem);
    assert(vlc_sem_wait_i11e(&sem) == 0);
    assert(vlc_mwait_i11e(1) == 0);
    assert(vlc_poll_i11e(NULL, 0, 1) == 0);

    vlc_interrupt_register(unreachable_callback, NULL);
    vlc_interrupt_unregister();

    void *data[2];
    vlc_interrupt_forward_start(ctx, data);
    assert(vlc_interrupt_forward_stop(data) == 0);

    vlc_close(fds[1]);
    vlc_close(fds[0]);
    vlc_sem_destroy(&sem);
    return 0;
}