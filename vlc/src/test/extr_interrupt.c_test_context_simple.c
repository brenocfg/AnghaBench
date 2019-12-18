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

/* Variables and functions */
 int CLOCK_FREQ ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/ * fds ; 
 int /*<<< orphan*/  interrupt_callback ; 
 int /*<<< orphan*/  sem ; 
 scalar_t__ vlc_accept_i11e (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_interrupt_raise (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_interrupt_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_unregister () ; 
 scalar_t__ vlc_mwait_i11e (int) ; 
 int vlc_poll_i11e (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int vlc_read_i11e (int /*<<< orphan*/ ,char*,int) ; 
 int vlc_recvfrom_i11e (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_sem_post (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_sem_wait_i11e (int /*<<< orphan*/ *) ; 
 int vlc_sendto_i11e (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vlc_write_i11e (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void test_context_simple(vlc_interrupt_t *ctx)
{
    vlc_interrupt_t *octx;
    char c;

    vlc_interrupt_set(ctx);
    octx = vlc_interrupt_set(NULL);
    assert(octx == ctx);
    octx = vlc_interrupt_set(ctx);
    assert(octx == NULL);
    octx = vlc_interrupt_set(ctx);
    assert(octx == ctx);

    vlc_interrupt_register(interrupt_callback, &sem);
    vlc_interrupt_raise(ctx);
    vlc_sem_wait(&sem);
    vlc_interrupt_unregister();

    /* BIG FAT WARNING: This is only meant to test the vlc_cond_wait_i11e()
     * function. This is NOT a good example of how to use the function in
     * normal code. */
    vlc_sem_post(&sem);
    assert(vlc_sem_wait_i11e(&sem) == 0);

    vlc_interrupt_raise(ctx);
    assert(vlc_sem_wait_i11e(&sem) == EINTR);

    vlc_sem_post(&sem);
    vlc_interrupt_raise(ctx);
    assert(vlc_sem_wait_i11e(&sem) == EINTR);
    assert(vlc_sem_wait_i11e(&sem) == 0);

    vlc_interrupt_raise(ctx);
    vlc_sem_post(&sem);
    assert(vlc_sem_wait_i11e(&sem) == EINTR);
    assert(vlc_sem_wait_i11e(&sem) == 0);

    assert(vlc_mwait_i11e(1) == 0);
    vlc_interrupt_raise(ctx);
    assert(vlc_mwait_i11e(CLOCK_FREQ * 10000000) == EINTR);

    assert(vlc_poll_i11e(NULL, 0, 1) == 0);
    vlc_interrupt_raise(ctx);
    assert(vlc_poll_i11e(NULL, 0, 1000000000) == -1);
    assert(errno == EINTR);

    c = 12;
    assert(vlc_write_i11e(fds[0], &c, 1) == 1);
    c = 0;
    assert(vlc_read_i11e(fds[1], &c, 1) == 1 && c == 12);
    vlc_interrupt_raise(ctx);
    assert(vlc_read_i11e(fds[1], &c, 1) == -1);
    assert(errno == EINTR);

    c = 42;
    assert(vlc_sendto_i11e(fds[0], &c, 1, 0, NULL, 0) == 1);
    c = 0;
    assert(vlc_recvfrom_i11e(fds[1], &c, 1, 0, NULL, 0) == 1 && c == 42);
    vlc_interrupt_raise(ctx);
    assert(vlc_recvfrom_i11e(fds[1], &c, 1, 0, NULL, 0) == -1);
    assert(errno == EINTR);

    vlc_interrupt_raise(ctx);
    assert(vlc_accept_i11e(fds[1], NULL, NULL, true) < 0);

    octx = vlc_interrupt_set(NULL);
    assert(octx == ctx);
    octx = vlc_interrupt_set(NULL);
    assert(octx == NULL);
}