#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  p_awh; } ;
typedef  TYPE_1__ vout_display_sys_t ;
struct TYPE_8__ {unsigned int i_sar_num; unsigned int i_sar_den; unsigned int i_width; unsigned int i_height; int /*<<< orphan*/  i_visible_height; int /*<<< orphan*/  i_visible_width; } ;
typedef  TYPE_2__ video_format_t ;

/* Variables and functions */
 int /*<<< orphan*/  AWindowHandler_setVideoLayout (int /*<<< orphan*/ ,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  video_format_ApplyRotation (TYPE_2__*,TYPE_2__*) ; 

__attribute__((used)) static int UpdateVideoSize(vout_display_sys_t *sys, video_format_t *p_fmt)
{
    unsigned int i_width, i_height;
    unsigned int i_sar_num = 1, i_sar_den = 1;
    video_format_t rot_fmt;

    video_format_ApplyRotation(&rot_fmt, p_fmt);

    if (rot_fmt.i_sar_num != 0 && rot_fmt.i_sar_den != 0) {
        i_sar_num = rot_fmt.i_sar_num;
        i_sar_den = rot_fmt.i_sar_den;
    }
    i_width = rot_fmt.i_width;
    i_height = rot_fmt.i_height;

    AWindowHandler_setVideoLayout(sys->p_awh, i_width, i_height,
                                  rot_fmt.i_visible_width,
                                  rot_fmt.i_visible_height,
                                  i_sar_num, i_sar_den);
    return 0;
}