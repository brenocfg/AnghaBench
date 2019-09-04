#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_6__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t backbuffer_count; int flags; scalar_t__ auto_restore_display_mode; int /*<<< orphan*/  windowed; } ;
struct wined3d_swapchain {int /*<<< orphan*/  backup_wnd; scalar_t__ backup_dc; TYPE_4__* device; int /*<<< orphan*/  original_window_rect; int /*<<< orphan*/  device_window; TYPE_3__ desc; int /*<<< orphan*/  original_mode; int /*<<< orphan*/ ** back_buffers; int /*<<< orphan*/ * front_buffer; int /*<<< orphan*/  orig_gamma; } ;
typedef  size_t UINT ;
struct TYPE_12__ {TYPE_1__* ops; } ;
struct TYPE_11__ {TYPE_2__* adapter; int /*<<< orphan*/  wined3d; TYPE_6__* cs; } ;
struct TYPE_9__ {int /*<<< orphan*/  ordinal; } ;
struct TYPE_8__ {int /*<<< orphan*/  (* finish ) (TYPE_6__*,int /*<<< orphan*/ ) ;} ;
typedef  int /*<<< orphan*/  HRESULT ;

/* Variables and functions */
 int /*<<< orphan*/  DestroyWindow (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ERR (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ FAILED (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_swapchain*,...) ; 
 int /*<<< orphan*/  WARN (char*,size_t,...) ; 
 int /*<<< orphan*/  WINED3D_CS_QUEUE_DEFAULT ; 
 int WINED3D_SWAPCHAIN_RESTORE_WINDOW_RECT ; 
 int /*<<< orphan*/  heap_free (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stub1 (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_cs_destroy_object (TYPE_6__*,int /*<<< orphan*/ ,struct wined3d_swapchain*) ; 
 int /*<<< orphan*/  wined3d_device_release_focus_window (TYPE_4__*) ; 
 int /*<<< orphan*/  wined3d_device_restore_fullscreen_window (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wined3d_release_dc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  wined3d_set_adapter_display_mode (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wined3d_swapchain_destroy_object ; 
 int /*<<< orphan*/  wined3d_swapchain_set_gamma_ramp (struct wined3d_swapchain*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ wined3d_texture_decref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wined3d_texture_set_swapchain (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void swapchain_cleanup(struct wined3d_swapchain *swapchain)
{
    HRESULT hr;
    UINT i;

    TRACE("Destroying swapchain %p.\n", swapchain);

    wined3d_swapchain_set_gamma_ramp(swapchain, 0, &swapchain->orig_gamma);

    /* Release the swapchain's draw buffers. Make sure swapchain->back_buffers[0]
     * is the last buffer to be destroyed, FindContext() depends on that. */
    if (swapchain->front_buffer)
    {
        wined3d_texture_set_swapchain(swapchain->front_buffer, NULL);
        if (wined3d_texture_decref(swapchain->front_buffer))
            WARN("Something's still holding the front buffer (%p).\n", swapchain->front_buffer);
        swapchain->front_buffer = NULL;
    }

    if (swapchain->back_buffers)
    {
        i = swapchain->desc.backbuffer_count;

        while (i--)
        {
            wined3d_texture_set_swapchain(swapchain->back_buffers[i], NULL);
            if (wined3d_texture_decref(swapchain->back_buffers[i]))
                WARN("Something's still holding back buffer %u (%p).\n", i, swapchain->back_buffers[i]);
        }
        heap_free(swapchain->back_buffers);
        swapchain->back_buffers = NULL;
    }

    wined3d_cs_destroy_object(swapchain->device->cs, wined3d_swapchain_destroy_object, swapchain);
    swapchain->device->cs->ops->finish(swapchain->device->cs, WINED3D_CS_QUEUE_DEFAULT);

    /* Restore the screen resolution if we rendered in fullscreen.
     * This will restore the screen resolution to what it was before creating
     * the swapchain. In case of d3d8 and d3d9 this will be the original
     * desktop resolution. In case of d3d7 this will be a NOP because ddraw
     * sets the resolution before starting up Direct3D, thus orig_width and
     * orig_height will be equal to the modes in the presentation params. */
    if (!swapchain->desc.windowed && swapchain->desc.auto_restore_display_mode)
    {
        if (FAILED(hr = wined3d_set_adapter_display_mode(swapchain->device->wined3d,
                swapchain->device->adapter->ordinal, &swapchain->original_mode)))
            ERR("Failed to restore display mode, hr %#x.\n", hr);

        if (swapchain->desc.flags & WINED3D_SWAPCHAIN_RESTORE_WINDOW_RECT)
        {
            wined3d_device_restore_fullscreen_window(swapchain->device, swapchain->device_window,
                    &swapchain->original_window_rect);
            wined3d_device_release_focus_window(swapchain->device);
        }
    }

    if (swapchain->backup_dc)
    {
        TRACE("Destroying backup wined3d window %p, dc %p.\n", swapchain->backup_wnd, swapchain->backup_dc);

        wined3d_release_dc(swapchain->backup_wnd, swapchain->backup_dc);
        DestroyWindow(swapchain->backup_wnd);
    }
}