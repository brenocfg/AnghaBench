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
typedef  int /*<<< orphan*/  GCancellable ;

/* Variables and functions */
 int /*<<< orphan*/  cancellable_interrupted ; 
 int /*<<< orphan*/ * g_cancellable_new () ; 
 int /*<<< orphan*/  vlc_interrupt_register (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static GCancellable *cancellable_register()
{
    GCancellable *p_canc = g_cancellable_new();
    if (!p_canc)
        return NULL;
    vlc_interrupt_register(cancellable_interrupted, p_canc);
    return p_canc;
}