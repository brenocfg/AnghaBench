#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  filter_t ;
struct TYPE_5__ {int /*<<< orphan*/  dec_device; int /*<<< orphan*/  conf; int /*<<< orphan*/  dpy; int /*<<< orphan*/  ctx; int /*<<< orphan*/  buf; } ;
struct TYPE_6__ {TYPE_1__ va; int /*<<< orphan*/  dest_pics; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/ * VLC_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  picture_pool_Release (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_vaapi_DestroyBuffer (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_vaapi_DestroyConfig (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_vaapi_DestroyContext (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_vaapi_FilterReleaseInstance (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
Close(filter_t *filter, filter_sys_t * filter_sys)
{
    vlc_object_t * obj = VLC_OBJECT(filter);
    picture_pool_Release(filter_sys->dest_pics);
    vlc_vaapi_DestroyBuffer(obj, filter_sys->va.dpy, filter_sys->va.buf);
    vlc_vaapi_DestroyContext(obj, filter_sys->va.dpy, filter_sys->va.ctx);
    vlc_vaapi_DestroyConfig(obj, filter_sys->va.dpy, filter_sys->va.conf);
    vlc_vaapi_FilterReleaseInstance(filter, filter_sys->va.dec_device);
    free(filter_sys);
}