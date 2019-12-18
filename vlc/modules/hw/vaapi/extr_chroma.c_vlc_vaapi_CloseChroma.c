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
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ filter_t ;
struct TYPE_6__ {int /*<<< orphan*/  cache; int /*<<< orphan*/ * dec_device; scalar_t__ dest_pics; } ;
typedef  TYPE_2__ filter_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  CopyCleanCache (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (TYPE_2__* const) ; 
 int /*<<< orphan*/  picture_pool_Release (scalar_t__) ; 
 int /*<<< orphan*/  vlc_vaapi_FilterReleaseInstance (TYPE_1__*,int /*<<< orphan*/ *) ; 

void
vlc_vaapi_CloseChroma(vlc_object_t *obj)
{
    filter_t *filter = (filter_t *)obj;
    filter_sys_t *const filter_sys = filter->p_sys;

    if (filter_sys->dest_pics)
        picture_pool_Release(filter_sys->dest_pics);
    if (filter_sys->dec_device != NULL)
        vlc_vaapi_FilterReleaseInstance(filter, filter_sys->dec_device);
    CopyCleanCache(&filter_sys->cache);

    free(filter_sys);
}