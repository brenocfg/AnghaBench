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
struct wined3d_swapchain {int /*<<< orphan*/  render_to_fbo; int /*<<< orphan*/  ds_format; } ;
struct wined3d_rendertarget_view {int /*<<< orphan*/  format; } ;
struct TYPE_3__ {int /*<<< orphan*/  sub_resource_idx; TYPE_2__* texture; } ;
struct wined3d_context {TYPE_1__ current_rt; scalar_t__ render_offscreen; } ;
struct TYPE_4__ {struct wined3d_swapchain* swapchain; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*) ; 
 int /*<<< orphan*/  WINED3D_LOCATION_TEXTURE_RGB ; 
 int /*<<< orphan*/  context_set_render_offscreen (struct wined3d_context*,int /*<<< orphan*/ ) ; 
 scalar_t__ match_depth_stencil_format (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  swapchain_update_draw_bindings (struct wined3d_swapchain*) ; 
 int /*<<< orphan*/  wined3d_texture_load_location (TYPE_2__*,int /*<<< orphan*/ ,struct wined3d_context*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void context_validate_onscreen_formats(struct wined3d_context *context,
        const struct wined3d_rendertarget_view *depth_stencil)
{
    /* Onscreen surfaces are always in a swapchain */
    struct wined3d_swapchain *swapchain = context->current_rt.texture->swapchain;

    if (context->render_offscreen || !depth_stencil) return;
    if (match_depth_stencil_format(swapchain->ds_format, depth_stencil->format)) return;

    /* TODO: If the requested format would satisfy the needs of the existing one(reverse match),
     * or no onscreen depth buffer was created, the OpenGL drawable could be changed to the new
     * format. */
    WARN("Depth stencil format is not supported by WGL, rendering the backbuffer in an FBO\n");

    /* The currently active context is the necessary context to access the swapchain's onscreen buffers */
    if (!(wined3d_texture_load_location(context->current_rt.texture, context->current_rt.sub_resource_idx,
            context, WINED3D_LOCATION_TEXTURE_RGB)))
        ERR("Failed to load location.\n");
    swapchain->render_to_fbo = TRUE;
    swapchain_update_draw_bindings(swapchain);
    context_set_render_offscreen(context, TRUE);
}