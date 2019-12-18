#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  anativewindow; } ;
struct TYPE_5__ {TYPE_1__ handle; } ;
typedef  TYPE_2__ vout_window_t ;

/* Variables and functions */
 int /*<<< orphan*/  AWindowHandler_destroy (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Close(vout_window_t *wnd)
{
    AWindowHandler_destroy(wnd->handle.anativewindow);
}