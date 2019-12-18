#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int interrupted; int /*<<< orphan*/  lock; int /*<<< orphan*/ * callback; } ;
typedef  TYPE_1__ vlc_interrupt_t ;

/* Variables and functions */
 int EINTR ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* vlc_interrupt_var ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlc_interrupt_finish(vlc_interrupt_t *ctx)
{
    int ret = 0;

    assert(ctx != NULL);
    assert(ctx == vlc_interrupt_var);

    /* Wait for pending callbacks to prevent access by other threads. */
    vlc_mutex_lock(&ctx->lock);
    ctx->callback = NULL;
    if (ctx->interrupted)
    {
        ret = EINTR;
        ctx->interrupted = false;
    }
    vlc_mutex_unlock(&ctx->lock);
    return ret;
}