#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  const* vlc_tick_t ;
typedef  int /*<<< orphan*/  video_format_t ;
struct TYPE_6__ {int /*<<< orphan*/ * p_sys; } ;
struct TYPE_7__ {TYPE_1__ updater; } ;
typedef  TYPE_2__ subpicture_t ;
typedef  int /*<<< orphan*/  bluray_spu_updater_sys_t ;
struct TYPE_8__ {scalar_t__ status; } ;
typedef  TYPE_3__ bluray_overlay_t ;

/* Variables and functions */
 scalar_t__ Outdated ; 
 int /*<<< orphan*/  VLC_UNUSED (int) ; 
 TYPE_3__* updater_lock_overlay (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  updater_unlock_overlay (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int subpictureUpdaterValidate(subpicture_t *p_subpic,
                                      bool b_fmt_src, const video_format_t *p_fmt_src,
                                      bool b_fmt_dst, const video_format_t *p_fmt_dst,
                                      vlc_tick_t i_ts)
{
    VLC_UNUSED(b_fmt_src);
    VLC_UNUSED(b_fmt_dst);
    VLC_UNUSED(p_fmt_src);
    VLC_UNUSED(p_fmt_dst);
    VLC_UNUSED(i_ts);

    bluray_spu_updater_sys_t *p_upd_sys = p_subpic->updater.p_sys;
    bluray_overlay_t         *p_overlay = updater_lock_overlay(p_upd_sys);

    if (!p_overlay) {
        return 1;
    }

    int res = p_overlay->status == Outdated;

    updater_unlock_overlay(p_upd_sys);

    return res;
}