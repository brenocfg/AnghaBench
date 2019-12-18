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
 int /*<<< orphan*/ * vlc_interrupt_var ; 

vlc_interrupt_t *vlc_interrupt_set(vlc_interrupt_t *newctx)
{
    vlc_interrupt_t *oldctx = vlc_interrupt_var;

    vlc_interrupt_var = newctx;
    return oldctx;
}