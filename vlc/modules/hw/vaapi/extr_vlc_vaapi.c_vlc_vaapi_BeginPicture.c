#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  VASurfaceID ;
typedef  int /*<<< orphan*/  VADisplay ;
typedef  int /*<<< orphan*/  VAContextID ;

/* Variables and functions */
 int /*<<< orphan*/  VA_CALL (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int VLC_EGENERIC ; 
 int VLC_SUCCESS ; 
 int /*<<< orphan*/  vaBeginPicture ; 

int
vlc_vaapi_BeginPicture(vlc_object_t *o, VADisplay dpy,
                       VAContextID ctx, VASurfaceID surface)
{
    VA_CALL(o, vaBeginPicture, dpy, ctx, surface);
    return VLC_SUCCESS;
error: return VLC_EGENERIC;
}