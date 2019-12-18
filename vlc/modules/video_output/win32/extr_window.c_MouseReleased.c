#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_window_t ;
struct TYPE_6__ {int button_pressed; } ;
typedef  TYPE_2__ vout_window_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  ReleaseCapture () ; 
 int /*<<< orphan*/  vout_window_ReportMouseReleased (TYPE_1__*,unsigned int) ; 

__attribute__((used)) static void MouseReleased( vout_window_t *wnd, unsigned button )
{
    vout_window_sys_t *sys = wnd->sys;
    sys->button_pressed &= ~(1 << button);
    if( !sys->button_pressed )
        ReleaseCapture();
    vout_window_ReportMouseReleased(wnd, button);
}