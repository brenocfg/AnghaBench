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
struct wined3d_swapchain {unsigned int swap_interval; int /*<<< orphan*/  front_buffer; int /*<<< orphan*/  device; } ;
struct wined3d_gl_info {scalar_t__* supported; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  ERR (char*,unsigned int,struct wined3d_context*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GetLastError () ; 
 size_t WGL_EXT_SWAP_CONTROL ; 
 struct wined3d_context* context_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_release (struct wined3d_context*) ; 
 int /*<<< orphan*/  wglSwapIntervalEXT (unsigned int) ; 

void wined3d_swapchain_set_swap_interval(struct wined3d_swapchain *swapchain,
        unsigned int swap_interval)
{
    const struct wined3d_gl_info *gl_info;
    struct wined3d_context *context;

    swap_interval = swap_interval <= 4 ? swap_interval : 1;
    if (swapchain->swap_interval == swap_interval)
        return;

    swapchain->swap_interval = swap_interval;

    context = context_acquire(swapchain->device, swapchain->front_buffer, 0);
    gl_info = context->gl_info;

    if (gl_info->supported[WGL_EXT_SWAP_CONTROL])
    {
        if (!GL_EXTCALL(wglSwapIntervalEXT(swap_interval)))
            ERR("wglSwapIntervalEXT failed to set swap interval %d for context %p, last error %#x.\n",
                    swap_interval, context, GetLastError());
    }

    context_release(context);
}