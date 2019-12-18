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
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sem ; 
 int /*<<< orphan*/  test_context_simple (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_set (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_sem_wait (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_sem_wait_i11e (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void *test_thread_simple(void *data)
{
    vlc_interrupt_t *ctx = data;

    vlc_interrupt_set(ctx);
    assert(vlc_sem_wait_i11e(&sem) == EINTR);
    assert(vlc_sem_wait_i11e(&sem) == 0);
    vlc_sem_wait(&sem);

    test_context_simple(ctx);
    return NULL;
}