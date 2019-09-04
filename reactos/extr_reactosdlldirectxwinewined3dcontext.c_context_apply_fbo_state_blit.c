#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wined3d_resource {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  member_0; } ;
struct wined3d_rendertarget_info {unsigned int sub_resource_idx; int layer_count; struct wined3d_resource* resource; TYPE_1__ member_0; } ;
struct wined3d_context {TYPE_2__* blit_targets; } ;
struct TYPE_5__ {unsigned int sub_resource_idx; int layer_count; struct wined3d_resource* resource; } ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  context_apply_fbo_state (struct wined3d_context*,int /*<<< orphan*/ ,TYPE_2__*,struct wined3d_rendertarget_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

void context_apply_fbo_state_blit(struct wined3d_context *context, GLenum target,
        struct wined3d_resource *rt, unsigned int rt_sub_resource_idx,
        struct wined3d_resource *ds, unsigned int ds_sub_resource_idx, DWORD location)
{
    struct wined3d_rendertarget_info ds_info = {{0}};

    memset(context->blit_targets, 0, sizeof(context->blit_targets));
    if (rt)
    {
        context->blit_targets[0].resource = rt;
        context->blit_targets[0].sub_resource_idx = rt_sub_resource_idx;
        context->blit_targets[0].layer_count = 1;
    }

    if (ds)
    {
        ds_info.resource = ds;
        ds_info.sub_resource_idx = ds_sub_resource_idx;
        ds_info.layer_count = 1;
    }

    context_apply_fbo_state(context, target, context->blit_targets, &ds_info, location, location);
}