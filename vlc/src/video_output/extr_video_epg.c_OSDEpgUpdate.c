#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  TYPE_2__ const* vlc_tick_t ;
struct TYPE_11__ {int i_width; int i_sar_num; int i_sar_den; int i_visible_width; int i_x_offset; int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_y_offset; } ;
typedef  TYPE_2__ video_format_t ;
struct TYPE_10__ {int /*<<< orphan*/ * p_sys; } ;
struct TYPE_12__ {int i_original_picture_width; int /*<<< orphan*/  p_region; int /*<<< orphan*/  i_original_picture_height; TYPE_1__ updater; } ;
typedef  TYPE_4__ subpicture_t ;
typedef  int /*<<< orphan*/  epg_spu_updater_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_UNUSED (TYPE_2__ const*) ; 
 int /*<<< orphan*/  vout_BuildOSDEpg (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void OSDEpgUpdate(subpicture_t *subpic,
                         const video_format_t *fmt_src,
                         const video_format_t *fmt_dst,
                         vlc_tick_t ts)
{
    epg_spu_updater_sys_t *sys = subpic->updater.p_sys;
    VLC_UNUSED(fmt_src); VLC_UNUSED(ts);

    video_format_t fmt = *fmt_dst;
    fmt.i_width         = fmt.i_width         * fmt.i_sar_num / fmt.i_sar_den;
    fmt.i_visible_width = fmt.i_visible_width * fmt.i_sar_num / fmt.i_sar_den;
    fmt.i_x_offset      = fmt.i_x_offset      * fmt.i_sar_num / fmt.i_sar_den;

    subpic->i_original_picture_width  = fmt.i_visible_width;
    subpic->i_original_picture_height = fmt.i_visible_height;

    subpic->p_region = vout_BuildOSDEpg(sys,
                                        fmt.i_x_offset,
                                        fmt.i_y_offset,
                                        fmt.i_visible_width,
                                        fmt.i_visible_height);
}