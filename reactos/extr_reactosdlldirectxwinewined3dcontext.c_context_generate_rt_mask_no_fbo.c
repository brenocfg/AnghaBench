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
struct wined3d_resource {scalar_t__ type; TYPE_1__* format; } ;
struct wined3d_context {int dummy; } ;
struct TYPE_4__ {scalar_t__ swapchain; } ;
struct TYPE_3__ {scalar_t__ id; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 scalar_t__ WINED3DFMT_NULL ; 
 scalar_t__ WINED3D_RTYPE_BUFFER ; 
 int /*<<< orphan*/  context_generate_rt_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_generate_rt_mask_from_resource (struct wined3d_resource*) ; 
 int /*<<< orphan*/  context_get_offscreen_gl_buffer (struct wined3d_context const*) ; 
 TYPE_2__* texture_from_resource (struct wined3d_resource*) ; 

__attribute__((used)) static DWORD context_generate_rt_mask_no_fbo(const struct wined3d_context *context, struct wined3d_resource *rt)
{
    if (!rt || rt->format->id == WINED3DFMT_NULL)
        return 0;
    else if (rt->type != WINED3D_RTYPE_BUFFER && texture_from_resource(rt)->swapchain)
        return context_generate_rt_mask_from_resource(rt);
    else
        return context_generate_rt_mask(context_get_offscreen_gl_buffer(context));
}