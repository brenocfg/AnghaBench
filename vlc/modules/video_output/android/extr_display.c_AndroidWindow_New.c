#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int /*<<< orphan*/ * sys; } ;
typedef  TYPE_1__ vout_display_t ;
typedef  int /*<<< orphan*/  vout_display_sys_t ;
struct TYPE_13__ {scalar_t__ i_chroma; int orientation; } ;
typedef  TYPE_2__ video_format_t ;
typedef  enum AWindow_ID { ____Placeholder_AWindow_ID } AWindow_ID ;
struct TYPE_14__ {int id; int b_opaque; int i_android_hal; int i_angle; int i_pic_count; int /*<<< orphan*/  fmt; } ;
typedef  TYPE_3__ android_window ;

/* Variables and functions */
 int AWindow_Subtitles ; 
 int AWindow_Video ; 
 scalar_t__ AndroidWindow_ConnectSurface (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int ChromaToAndroidHal (scalar_t__) ; 
#define  ORIENT_ROTATED_180 130 
#define  ORIENT_ROTATED_270 129 
#define  ORIENT_ROTATED_90 128 
 scalar_t__ VLC_CODEC_ANDROID_OPAQUE ; 
 TYPE_3__* calloc (int,int) ; 
 int /*<<< orphan*/  free (TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  video_format_ApplyRotation (int /*<<< orphan*/ *,TYPE_2__ const*) ; 

__attribute__((used)) static android_window *AndroidWindow_New(vout_display_t *vd,
                                         const video_format_t *p_fmt,
                                         enum AWindow_ID id)
{
    vout_display_sys_t *sys = vd->sys;
    android_window *p_window = NULL;

    p_window = calloc(1, sizeof(android_window));
    if (!p_window)
        goto error;

    p_window->id = id;
    p_window->b_opaque = p_fmt->i_chroma == VLC_CODEC_ANDROID_OPAQUE;
    if (!p_window->b_opaque) {
        p_window->i_android_hal = ChromaToAndroidHal(p_fmt->i_chroma);
        if (p_window->i_android_hal == -1)
            goto error;
    }

    switch (p_fmt->orientation)
    {
        case ORIENT_ROTATED_90:
            p_window->i_angle = 90;
            break;
        case ORIENT_ROTATED_180:
            p_window->i_angle = 180;
            break;
        case ORIENT_ROTATED_270:
            p_window->i_angle = 270;
            break;
        default:
            p_window->i_angle = 0;
    }
    video_format_ApplyRotation(&p_window->fmt, p_fmt);
    p_window->i_pic_count = 1;

    if (AndroidWindow_ConnectSurface(sys, p_window) != 0)
    {
        if (id == AWindow_Video)
            msg_Err(vd, "can't get Video Surface");
        else if (id == AWindow_Subtitles)
            msg_Err(vd, "can't get Subtitles Surface");
        goto error;
    }

    return p_window;
error:
    free(p_window);
    return NULL;
}