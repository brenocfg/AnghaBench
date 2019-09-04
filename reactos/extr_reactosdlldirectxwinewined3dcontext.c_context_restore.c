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
struct TYPE_4__ {int /*<<< orphan*/  device; } ;
struct wined3d_texture {TYPE_2__ resource; } ;
struct TYPE_3__ {unsigned int sub_resource_idx; struct wined3d_texture* texture; } ;
struct wined3d_context {TYPE_1__ current_rt; } ;

/* Variables and functions */
 struct wined3d_context* context_acquire (int /*<<< orphan*/ ,struct wined3d_texture*,unsigned int) ; 
 int /*<<< orphan*/  context_release (struct wined3d_context*) ; 

void context_restore(struct wined3d_context *context, struct wined3d_texture *texture, unsigned int sub_resource_idx)
{
    if (context->current_rt.texture != texture || context->current_rt.sub_resource_idx != sub_resource_idx)
    {
        context_release(context);
        context = context_acquire(texture->resource.device, texture, sub_resource_idx);
    }

    context_release(context);
}