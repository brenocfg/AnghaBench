#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct wined3d_texture {struct wined3d_swapchain* swapchain; } ;
struct wined3d_swapchain {struct wined3d_texture* front_buffer; struct wined3d_texture** back_buffers; } ;
struct wined3d_device {struct wined3d_swapchain** swapchains; int /*<<< orphan*/  cs; } ;
struct TYPE_2__ {unsigned int sub_resource_idx; struct wined3d_texture* texture; } ;
struct wined3d_context {struct wined3d_device const* device; TYPE_1__ current_rt; scalar_t__ destroyed; } ;
typedef  int BOOL ;

/* Variables and functions */
 int /*<<< orphan*/  TRACE (char*,...) ; 
 int /*<<< orphan*/  context_activate (struct wined3d_context*,struct wined3d_texture*,unsigned int) ; 
 struct wined3d_context* context_get_current () ; 
 struct wined3d_context* swapchain_get_context (struct wined3d_swapchain*) ; 
 int /*<<< orphan*/  wined3d_from_cs (int /*<<< orphan*/ ) ; 

struct wined3d_context *context_acquire(const struct wined3d_device *device,
        struct wined3d_texture *texture, unsigned int sub_resource_idx)
{
    struct wined3d_context *current_context = context_get_current();
    struct wined3d_context *context;
    BOOL swapchain_texture;

    TRACE("device %p, texture %p, sub_resource_idx %u.\n", device, texture, sub_resource_idx);

    wined3d_from_cs(device->cs);

    if (current_context && current_context->destroyed)
        current_context = NULL;

    swapchain_texture = texture && texture->swapchain;
    if (!texture)
    {
        if (current_context
                && current_context->current_rt.texture
                && current_context->device == device)
        {
            texture = current_context->current_rt.texture;
            sub_resource_idx = current_context->current_rt.sub_resource_idx;
        }
        else
        {
            struct wined3d_swapchain *swapchain = device->swapchains[0];

            if (swapchain->back_buffers)
                texture = swapchain->back_buffers[0];
            else
                texture = swapchain->front_buffer;
            sub_resource_idx = 0;
        }
    }

    if (current_context && current_context->current_rt.texture == texture)
    {
        context = current_context;
    }
    else if (swapchain_texture)
    {
        TRACE("Rendering onscreen.\n");

        context = swapchain_get_context(texture->swapchain);
    }
    else
    {
        TRACE("Rendering offscreen.\n");

        /* Stay with the current context if possible. Otherwise use the
         * context for the primary swapchain. */
        if (current_context && current_context->device == device)
            context = current_context;
        else
            context = swapchain_get_context(device->swapchains[0]);
    }

    context_activate(context, texture, sub_resource_idx);

    return context;
}