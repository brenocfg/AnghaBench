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
struct TYPE_4__ {void (* callback ) (void*) ;int /*<<< orphan*/  lock; int /*<<< orphan*/  interrupted; void* data; } ;
typedef  TYPE_1__ vlc_interrupt_t ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 TYPE_1__* vlc_interrupt_var ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlc_interrupt_prepare(vlc_interrupt_t *ctx,
                                  void (*cb)(void *), void *data)
{
    assert(ctx != NULL);
    assert(ctx == vlc_interrupt_var);

    vlc_mutex_lock(&ctx->lock);
    assert(ctx->callback == NULL);
    ctx->callback = cb;
    ctx->data = data;

    if (unlikely(ctx->interrupted))
        cb(data);
    vlc_mutex_unlock(&ctx->lock);
}