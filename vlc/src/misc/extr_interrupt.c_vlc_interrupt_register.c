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
 int /*<<< orphan*/  vlc_interrupt_prepare (int /*<<< orphan*/ *,void (*) (void*),void*) ; 
 int /*<<< orphan*/ * vlc_interrupt_var ; 

void vlc_interrupt_register(void (*cb)(void *), void *opaque)
{
    vlc_interrupt_t *ctx = vlc_interrupt_var;
    if (ctx != NULL)
        vlc_interrupt_prepare(ctx, cb, opaque);
}