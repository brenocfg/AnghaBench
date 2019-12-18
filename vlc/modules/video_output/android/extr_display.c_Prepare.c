#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_15__ ;

/* Type definitions */
struct TYPE_18__ {TYPE_3__* sys; } ;
typedef  TYPE_2__ vout_display_t ;
struct TYPE_19__ {int b_sub_invalid; int b_has_subpictures; TYPE_1__* p_window; int /*<<< orphan*/ * p_spu_blend; TYPE_5__* p_sub_pic; TYPE_15__* p_sub_window; int /*<<< orphan*/ * p_sub_buffer_bounds; int /*<<< orphan*/  p_prepared_pic; } ;
typedef  TYPE_3__ vout_display_sys_t ;
typedef  scalar_t__ vlc_tick_t ;
typedef  int /*<<< orphan*/  subpicture_t ;
struct TYPE_20__ {int /*<<< orphan*/  p_sys; } ;
typedef  TYPE_4__ picture_t ;
struct TYPE_21__ {int /*<<< orphan*/  format; } ;
struct TYPE_17__ {scalar_t__ b_opaque; } ;
struct TYPE_16__ {int /*<<< orphan*/  fmt; } ;

/* Variables and functions */
 scalar_t__ AndroidOpaquePicture_CanReleaseAtTime (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  AndroidOpaquePicture_ReleaseAtTime (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ AndroidWindow_Setup (TYPE_3__*,TYPE_15__*,int) ; 
 TYPE_5__* PictureAlloc (TYPE_3__*,int /*<<< orphan*/ *,int) ; 
 scalar_t__ PoolLockPicture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PoolUnlockPicture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SubpicturePrepare (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  VLC_OBJECT (TYPE_2__*) ; 
 scalar_t__ VLC_TICK_FROM_SEC (int) ; 
 int /*<<< orphan*/  filter_DeleteBlend (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * filter_NewBlend (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_2__*,char*) ; 
 int /*<<< orphan*/  picture_Copy (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  picture_Release (TYPE_5__*) ; 
 scalar_t__ vlc_tick_now () ; 

__attribute__((used)) static void Prepare(vout_display_t *vd, picture_t *picture,
                    subpicture_t *subpicture, vlc_tick_t date)
{
    vout_display_sys_t *sys = vd->sys;

    if (!sys->p_window->b_opaque)
    {
        if (PoolLockPicture(sys->p_prepared_pic) == 0)
        {
            picture_Copy(sys->p_prepared_pic, picture);
            PoolUnlockPicture(sys->p_prepared_pic);
        }
    }

    if (subpicture && sys->p_sub_window) {
        if (sys->b_sub_invalid) {
            sys->b_sub_invalid = false;
            if (sys->p_sub_pic) {
                picture_Release(sys->p_sub_pic);
                sys->p_sub_pic = NULL;
            }
            if (sys->p_spu_blend) {
                filter_DeleteBlend(sys->p_spu_blend);
                sys->p_spu_blend = NULL;
            }
            free(sys->p_sub_buffer_bounds);
            sys->p_sub_buffer_bounds = NULL;
        }

        if (!sys->p_sub_pic
         && AndroidWindow_Setup(sys, sys->p_sub_window, 1) == 0)
            sys->p_sub_pic = PictureAlloc(sys, &sys->p_sub_window->fmt, false);
        if (!sys->p_spu_blend && sys->p_sub_pic)
            sys->p_spu_blend = filter_NewBlend(VLC_OBJECT(vd),
                                               &sys->p_sub_pic->format);

        if (sys->p_sub_pic && sys->p_spu_blend)
            sys->b_has_subpictures = true;
    }
    /* As long as no subpicture was received, do not call
       SubpictureDisplay since JNI calls and clearing the subtitles
       surface are expensive operations. */
    if (sys->b_has_subpictures)
    {
        SubpicturePrepare(vd, subpicture);
        if (!subpicture)
        {
            /* The surface has been cleared and there is no new
               subpicture to upload, do not clear again until a new
               subpicture is received. */
            sys->b_has_subpictures = false;
        }
    }
    if (sys->p_window->b_opaque
     && AndroidOpaquePicture_CanReleaseAtTime(picture->p_sys))
    {
        vlc_tick_t now = vlc_tick_now();
        if (date > now)
        {
            if (date - now <= VLC_TICK_FROM_SEC(1))
                AndroidOpaquePicture_ReleaseAtTime(picture->p_sys, date);
            else /* The picture will be displayed from the Display callback */
                msg_Warn(vd, "picture way too early to release at time");
        }
    }
}