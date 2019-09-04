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
struct wined3d_context {scalar_t__ win_handle; int needs_set; int valid; scalar_t__ hdc; void* hdc_has_format; void* hdc_is_private; TYPE_1__* swapchain; } ;
struct TYPE_2__ {scalar_t__ win_handle; } ;

/* Variables and functions */
 int DCX_CACHE ; 
 int DCX_USESTYLE ; 
 int /*<<< orphan*/  ERR (char*,scalar_t__) ; 
 void* FALSE ; 
 scalar_t__ GetDCEx (scalar_t__,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_context*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wined3d_release_dc (scalar_t__,scalar_t__) ; 

__attribute__((used)) static void context_update_window(struct wined3d_context *context)
{
    if (!context->swapchain)
        return;

    if (context->win_handle == context->swapchain->win_handle)
        return;

    TRACE("Updating context %p window from %p to %p.\n",
            context, context->win_handle, context->swapchain->win_handle);

    if (context->hdc)
        wined3d_release_dc(context->win_handle, context->hdc);

    context->win_handle = context->swapchain->win_handle;
    context->hdc_is_private = FALSE;
    context->hdc_has_format = FALSE;
    context->needs_set = 1;
    context->valid = 1;

    if (!(context->hdc = GetDCEx(context->win_handle, 0, DCX_USESTYLE | DCX_CACHE)))
    {
        ERR("Failed to get a device context for window %p.\n", context->win_handle);
        context->valid = 0;
    }
}