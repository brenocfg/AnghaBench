#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_window_t ;
struct TYPE_8__ {int /*<<< orphan*/  wm_state_fullscreen; } ;
typedef  TYPE_2__ vout_window_sys_t ;
struct TYPE_9__ {int /*<<< orphan*/  is_fullscreen; } ;
typedef  TYPE_3__ vout_window_cfg_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  change_wm_state (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int EmEnable(vout_window_t *wnd, const vout_window_cfg_t *restrict cfg)
{
    vout_window_sys_t *sys = wnd->sys;

    change_wm_state(wnd, cfg->is_fullscreen, sys->wm_state_fullscreen);
    return VLC_SUCCESS;
}