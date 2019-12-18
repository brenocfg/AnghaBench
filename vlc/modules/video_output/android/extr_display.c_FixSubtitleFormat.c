#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int i_display_height; int i_display_width; int b_sub_invalid; TYPE_2__* p_window; TYPE_1__* p_sub_window; } ;
typedef  TYPE_3__ vout_display_sys_t ;
struct TYPE_10__ {int i_visible_width; int i_visible_height; int i_width; int i_height; int i_sar_num; int i_sar_den; scalar_t__ i_y_offset; scalar_t__ i_x_offset; } ;
typedef  TYPE_4__ video_format_t ;
struct TYPE_8__ {int i_angle; int /*<<< orphan*/  fmt; } ;
struct TYPE_7__ {TYPE_4__ fmt; } ;

/* Variables and functions */
 int /*<<< orphan*/  video_format_ApplyRotation (TYPE_4__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void FixSubtitleFormat(vout_display_sys_t *sys)
{
    video_format_t *p_subfmt;
    video_format_t fmt;
    int i_width, i_height;
    int i_video_width, i_video_height;
    int i_display_width, i_display_height;
    double aspect;

    if (!sys->p_sub_window)
        return;
    p_subfmt = &sys->p_sub_window->fmt;

    video_format_ApplyRotation(&fmt, &sys->p_window->fmt);

    if (fmt.i_visible_width == 0 || fmt.i_visible_height == 0) {
        i_video_width = fmt.i_width;
        i_video_height = fmt.i_height;
    } else {
        i_video_width = fmt.i_visible_width;
        i_video_height = fmt.i_visible_height;
    }

    if (fmt.i_sar_num > 0 && fmt.i_sar_den > 0) {
        if (fmt.i_sar_num >= fmt.i_sar_den)
            i_video_width = i_video_width * fmt.i_sar_num / fmt.i_sar_den;
        else
            i_video_height = i_video_height * fmt.i_sar_den / fmt.i_sar_num;
    }

    if (sys->p_window->i_angle == 90 || sys->p_window->i_angle == 180) {
        i_display_width = sys->i_display_height;
        i_display_height = sys->i_display_width;
        aspect = i_video_height / (double) i_video_width;
    } else {
        i_display_width = sys->i_display_width;
        i_display_height = sys->i_display_height;
        aspect = i_video_width / (double) i_video_height;
    }

    if (i_display_width / aspect < i_display_height) {
        i_width = i_display_width;
        i_height = i_display_width / aspect;
    } else {
        i_width = i_display_height * aspect;
        i_height = i_display_height;
    }

    // Use the biggest size available
    if (i_width * i_height < i_video_width * i_video_height) {
        i_width = i_video_width;
        i_height = i_video_height;
    }

    p_subfmt->i_width =
    p_subfmt->i_visible_width = i_width;
    p_subfmt->i_height =
    p_subfmt->i_visible_height = i_height;
    p_subfmt->i_x_offset = 0;
    p_subfmt->i_y_offset = 0;
    p_subfmt->i_sar_num = 1;
    p_subfmt->i_sar_den = 1;
    sys->b_sub_invalid = true;
}