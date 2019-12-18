#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  lock; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ vlc_interrupt_t ;
typedef  int /*<<< orphan*/  vlc_cond_t ;

/* Variables and functions */
 int /*<<< orphan*/  vlc_cond_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_finish (TYPE_1__*) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void vlc_mwait_i11e_cleanup(void *opaque)
{
    vlc_interrupt_t *ctx = opaque;
    vlc_cond_t *cond = ctx->data;

    vlc_mutex_unlock(&ctx->lock);
    vlc_interrupt_finish(ctx);
    vlc_cond_destroy(cond);
}