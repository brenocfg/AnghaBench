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
struct wined3d_texture {int /*<<< orphan*/  resource; struct wined3d_swapchain* swapchain; } ;
struct wined3d_swapchain {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wined3d_resource_update_draw_binding (int /*<<< orphan*/ *) ; 

void wined3d_texture_set_swapchain(struct wined3d_texture *texture, struct wined3d_swapchain *swapchain)
{
    texture->swapchain = swapchain;
    wined3d_resource_update_draw_binding(&texture->resource);
}