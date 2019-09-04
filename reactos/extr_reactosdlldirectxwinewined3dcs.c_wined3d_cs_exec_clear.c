#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wined3d_device {TYPE_4__* blitter; } ;
struct wined3d_cs_clear {unsigned int rt_count; int flags; TYPE_5__* fb; int /*<<< orphan*/  stencil; int /*<<< orphan*/  depth; int /*<<< orphan*/  color; int /*<<< orphan*/  draw_rect; int /*<<< orphan*/  rects; int /*<<< orphan*/  rect_count; } ;
struct wined3d_cs {struct wined3d_device* device; } ;
struct TYPE_10__ {TYPE_3__* depth_stencil; TYPE_2__** render_targets; } ;
struct TYPE_9__ {TYPE_1__* ops; } ;
struct TYPE_8__ {int /*<<< orphan*/  resource; } ;
struct TYPE_7__ {int /*<<< orphan*/  resource; } ;
struct TYPE_6__ {int /*<<< orphan*/  (* blitter_clear ) (TYPE_4__*,struct wined3d_device*,unsigned int,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 int WINED3DCLEAR_STENCIL ; 
 int WINED3DCLEAR_TARGET ; 
 int WINED3DCLEAR_ZBUFFER ; 
 int /*<<< orphan*/  stub1 (TYPE_4__*,struct wined3d_device*,unsigned int,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wined3d_resource_release (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void wined3d_cs_exec_clear(struct wined3d_cs *cs, const void *data)
{
    const struct wined3d_cs_clear *op = data;
    struct wined3d_device *device;
    unsigned int i;

    device = cs->device;
    device->blitter->ops->blitter_clear(device->blitter, device, op->rt_count, op->fb,
            op->rect_count, op->rects, &op->draw_rect, op->flags, &op->color, op->depth, op->stencil);

    if (op->flags & WINED3DCLEAR_TARGET)
    {
        for (i = 0; i < op->rt_count; ++i)
        {
            if (op->fb->render_targets[i])
                wined3d_resource_release(op->fb->render_targets[i]->resource);
        }
    }
    if (op->flags & (WINED3DCLEAR_ZBUFFER | WINED3DCLEAR_STENCIL))
        wined3d_resource_release(op->fb->depth_stencil->resource);
}