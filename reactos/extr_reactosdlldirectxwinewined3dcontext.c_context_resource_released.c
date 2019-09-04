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
struct wined3d_resource {int dummy; } ;
struct wined3d_device {unsigned int context_count; struct wined3d_context** contexts; int /*<<< orphan*/  d3d_initialized; } ;
struct TYPE_4__ {scalar_t__ sub_resource_idx; TYPE_1__* texture; } ;
struct wined3d_context {TYPE_2__ current_rt; } ;
struct TYPE_3__ {struct wined3d_resource resource; } ;

/* Variables and functions */

void context_resource_released(const struct wined3d_device *device, struct wined3d_resource *resource)
{
    unsigned int i;

    if (!device->d3d_initialized)
        return;

    for (i = 0; i < device->context_count; ++i)
    {
        struct wined3d_context *context = device->contexts[i];

        if (&context->current_rt.texture->resource == resource)
        {
            context->current_rt.texture = NULL;
            context->current_rt.sub_resource_idx = 0;
        }
    }
}