#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct TYPE_6__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  interrupted; } ;
typedef  TYPE_1__ vlc_interrupt_t ;
typedef  int /*<<< orphan*/  vlc_cond_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_cleanup_push (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_cond_init (int /*<<< orphan*/ *) ; 
 scalar_t__ vlc_cond_timedwait (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int vlc_interrupt_finish (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_interrupt_prepare (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_1__* vlc_interrupt_var ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mwait_i11e_cleanup ; 
 int /*<<< orphan*/  vlc_mwait_i11e_wake ; 
 int vlc_tick_wait (int /*<<< orphan*/ ) ; 

int vlc_mwait_i11e(vlc_tick_t deadline)
{
    vlc_interrupt_t *ctx = vlc_interrupt_var;
    if (ctx == NULL)
        return vlc_tick_wait(deadline), 0;

    vlc_cond_t wait;
    vlc_cond_init(&wait);

    vlc_interrupt_prepare(ctx, vlc_mwait_i11e_wake, &wait);

    vlc_mutex_lock(&ctx->lock);
    vlc_cleanup_push(vlc_mwait_i11e_cleanup, ctx);
    while (!ctx->interrupted
        && vlc_cond_timedwait(&wait, &ctx->lock, deadline) == 0);
    vlc_cleanup_pop();
    vlc_mutex_unlock(&ctx->lock);

    int ret = vlc_interrupt_finish(ctx);
    vlc_cond_destroy(&wait);
    return ret;
}