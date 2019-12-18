#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;

/* Type definitions */
struct TYPE_21__ {TYPE_1__* anw; } ;
typedef  TYPE_5__ vout_display_sys_t ;
struct TYPE_22__ {TYPE_3__* p; TYPE_7__* p_sys; } ;
typedef  TYPE_6__ picture_t ;
struct TYPE_25__ {scalar_t__ width; scalar_t__ height; int stride; scalar_t__ format; int /*<<< orphan*/  bits; } ;
struct TYPE_20__ {TYPE_9__ buf; } ;
struct TYPE_23__ {int b_locked; TYPE_4__ sw; } ;
typedef  TYPE_7__ picture_sys_t ;
struct TYPE_18__ {unsigned int i_width; unsigned int i_height; } ;
struct TYPE_24__ {TYPE_2__ fmt; int /*<<< orphan*/  p_surface; } ;
typedef  TYPE_8__ android_window ;
struct TYPE_19__ {scalar_t__ i_lines; int i_pitch; int i_pixel_pitch; int /*<<< orphan*/  p_pixels; } ;
struct TYPE_17__ {scalar_t__ (* winLock ) (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ *) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  AndroidWindow_UnlockPicture (TYPE_5__*,TYPE_8__*,TYPE_6__*) ; 
 scalar_t__ PRIV_WINDOW_FORMAT_YV12 ; 
 int /*<<< orphan*/  SetupPictureYV12 (TYPE_6__*,int) ; 
 scalar_t__ stub1 (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int AndroidWindow_LockPicture(vout_display_sys_t *sys,
                                     android_window *p_window,
                                     picture_t *p_pic)
{
    picture_sys_t *p_picsys = p_pic->p_sys;

    if (p_picsys->b_locked)
        return -1;

    if (sys->anw->winLock(p_window->p_surface,
                          &p_picsys->sw.buf, NULL) != 0)
        return -1;

    if (p_picsys->sw.buf.width < 0 ||
        p_picsys->sw.buf.height < 0 ||
        (unsigned)p_picsys->sw.buf.width < p_window->fmt.i_width ||
        (unsigned)p_picsys->sw.buf.height < p_window->fmt.i_height)
    {
        p_picsys->b_locked = true;
        AndroidWindow_UnlockPicture(sys, p_window, p_pic);
        return -1;
    }

    p_pic->p[0].p_pixels = p_picsys->sw.buf.bits;
    p_pic->p[0].i_lines = p_picsys->sw.buf.height;
    p_pic->p[0].i_pitch = p_pic->p[0].i_pixel_pitch * p_picsys->sw.buf.stride;

    if (p_picsys->sw.buf.format == PRIV_WINDOW_FORMAT_YV12)
        SetupPictureYV12(p_pic, p_picsys->sw.buf.stride);

    p_picsys->b_locked = true;
    return 0;
}