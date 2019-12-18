#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  hwnd; } ;
typedef  TYPE_1__ vout_window_sys_t ;
struct vout_window_t {TYPE_1__* sys; } ;

/* Variables and functions */
 int /*<<< orphan*/  SW_HIDE ; 
 int /*<<< orphan*/  ShowWindow (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void Disable(struct vout_window_t *wnd)
{
    vout_window_sys_t *sys = wnd->sys;
    ShowWindow( sys->hwnd, SW_HIDE );
}