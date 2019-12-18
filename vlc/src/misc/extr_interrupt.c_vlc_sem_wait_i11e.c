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
typedef  int /*<<< orphan*/  vlc_sem_t ;
typedef  int /*<<< orphan*/  vlc_interrupt_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cleanup_push (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_cleanup ; 
 int vlc_interrupt_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_prepare (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_sem ; 
 int /*<<< orphan*/ * vlc_interrupt_var ; 
 int vlc_sem_wait (int /*<<< orphan*/ *) ; 

int vlc_sem_wait_i11e(vlc_sem_t *sem)
{
    vlc_interrupt_t *ctx = vlc_interrupt_var;
    if (ctx == NULL)
        return vlc_sem_wait(sem), 0;

    vlc_interrupt_prepare(ctx, vlc_interrupt_sem, sem);

    vlc_cleanup_push(vlc_interrupt_cleanup, ctx);
    vlc_sem_wait(sem);
    vlc_cleanup_pop();

    return vlc_interrupt_finish(ctx);
}