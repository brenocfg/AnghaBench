#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  sys; } ;
typedef  TYPE_1__ vout_display_t ;
typedef  int /*<<< orphan*/ * vlc_tick_t ;
typedef  int /*<<< orphan*/  subpicture_t ;
typedef  int /*<<< orphan*/  picture_t ;

/* Variables and functions */
 scalar_t__ KVALock (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  KVAUnlock (int /*<<< orphan*/ *) ; 
 scalar_t__ VLC_SUCCESS ; 
 int /*<<< orphan*/  VLC_UNUSED (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  picture_CopyPixels (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Prepare(vout_display_t *vd, picture_t *pic, subpicture_t *subpic, vlc_tick_t date)
{
    VLC_UNUSED(subpic);
    VLC_UNUSED(date);
    picture_t fake_pic = *pic;
    if (KVALock(vd->sys, &fake_pic) == VLC_SUCCESS)
    {
        picture_CopyPixels(&fake_pic, pic);
        KVAUnlock(&fake_pic);
    }
}