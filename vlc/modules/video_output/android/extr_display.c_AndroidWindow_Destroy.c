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
struct TYPE_3__ {int /*<<< orphan*/  sys; } ;
typedef  TYPE_1__ vout_display_t ;
typedef  int /*<<< orphan*/  android_window ;

/* Variables and functions */
 int /*<<< orphan*/  AndroidWindow_DisconnectSurface (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void AndroidWindow_Destroy(vout_display_t *vd,
                                  android_window *p_window)
{
    AndroidWindow_DisconnectSurface(vd->sys, p_window);
    free(p_window);
}