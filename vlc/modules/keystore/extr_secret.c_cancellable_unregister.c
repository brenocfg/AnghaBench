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
 int /*<<< orphan*/  g_object_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_interrupt_unregister () ; 

__attribute__((used)) static void cancellable_unregister(GCancellable *p_canc)
{
    if (p_canc != NULL)
    {
        vlc_interrupt_unregister();
        g_object_unref(p_canc);
    }
}