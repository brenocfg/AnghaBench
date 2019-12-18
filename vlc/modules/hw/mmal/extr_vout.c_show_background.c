#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_2__* sys; } ;
typedef  TYPE_1__ vout_display_t ;
struct TYPE_5__ {void* bkg_resource; void* bkg_element; scalar_t__ layer; int /*<<< orphan*/  dmx_handle; } ;
typedef  TYPE_2__ vout_display_sys_t ;
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  color ;
typedef  int /*<<< orphan*/  VC_RECT_T ;
typedef  int /*<<< orphan*/  DISPMANX_UPDATE_HANDLE_T ;

/* Variables and functions */
 void* DISPMANX_NO_HANDLE ; 
 int /*<<< orphan*/  DISPMANX_PROTECTION_NONE ; 
 int /*<<< orphan*/  VC_IMAGE_RGBA32 ; 
 int /*<<< orphan*/  VC_IMAGE_ROT0 ; 
 void* vc_dispmanx_element_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ *,void*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_element_remove (int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  vc_dispmanx_rect_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 void* vc_dispmanx_resource_create (int /*<<< orphan*/ ,int,int,int*) ; 
 int /*<<< orphan*/  vc_dispmanx_resource_delete (void*) ; 
 int /*<<< orphan*/  vc_dispmanx_resource_write_data (void*,int /*<<< orphan*/ ,int,int*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vc_dispmanx_update_start (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vc_dispmanx_update_submit_sync (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void show_background(vout_display_t *vd, bool enable)
{
    vout_display_sys_t *sys = vd->sys;
    uint32_t image_ptr, color = 0xFF000000;
    VC_RECT_T dst_rect, src_rect;
    DISPMANX_UPDATE_HANDLE_T update;

    if (enable && !sys->bkg_element) {
        sys->bkg_resource = vc_dispmanx_resource_create(VC_IMAGE_RGBA32, 1, 1,
                        &image_ptr);
        vc_dispmanx_rect_set(&dst_rect, 0, 0, 1, 1);
        vc_dispmanx_resource_write_data(sys->bkg_resource, VC_IMAGE_RGBA32,
                        sizeof(color), &color, &dst_rect);
        vc_dispmanx_rect_set(&src_rect, 0, 0, 1 << 16, 1 << 16);
        vc_dispmanx_rect_set(&dst_rect, 0, 0, 0, 0);
        update = vc_dispmanx_update_start(0);
        sys->bkg_element = vc_dispmanx_element_add(update, sys->dmx_handle,
                        sys->layer - 1, &dst_rect, sys->bkg_resource, &src_rect,
                        DISPMANX_PROTECTION_NONE, NULL, NULL, VC_IMAGE_ROT0);
        vc_dispmanx_update_submit_sync(update);
    } else if (!enable && sys->bkg_element) {
        update = vc_dispmanx_update_start(0);
        vc_dispmanx_element_remove(update, sys->bkg_element);
        vc_dispmanx_resource_delete(sys->bkg_resource);
        vc_dispmanx_update_submit_sync(update);
        sys->bkg_element = DISPMANX_NO_HANDLE;
        sys->bkg_resource = DISPMANX_NO_HANDLE;
    }
}