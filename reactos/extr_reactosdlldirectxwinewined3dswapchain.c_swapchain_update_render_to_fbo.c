#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  backbuffer_count; } ;
struct wined3d_swapchain {int /*<<< orphan*/  render_to_fbo; TYPE_1__ desc; } ;
struct TYPE_4__ {scalar_t__ offscreen_rendering_mode; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 scalar_t__ ORM_FBO ; 
 int /*<<< orphan*/  TRACE (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__ wined3d_settings ; 

__attribute__((used)) static void swapchain_update_render_to_fbo(struct wined3d_swapchain *swapchain)
{
    if (wined3d_settings.offscreen_rendering_mode != ORM_FBO)
        return;

    if (!swapchain->desc.backbuffer_count)
    {
        TRACE("Single buffered rendering.\n");
        swapchain->render_to_fbo = FALSE;
        return;
    }

    TRACE("Rendering to FBO.\n");
    swapchain->render_to_fbo = TRUE;
}