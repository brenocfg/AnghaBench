#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct wined3d_cs {int /*<<< orphan*/  device; } ;
struct wined3d_context {TYPE_3__* gl_info; scalar_t__ valid; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* p_glFlush ) () ;} ;
struct TYPE_5__ {TYPE_1__ gl; } ;
struct TYPE_6__ {TYPE_2__ gl_ops; } ;

/* Variables and functions */
 struct wined3d_context* context_acquire (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_release (struct wined3d_context*) ; 
 int /*<<< orphan*/  stub1 () ; 

__attribute__((used)) static void wined3d_cs_exec_flush(struct wined3d_cs *cs, const void *data)
{
    struct wined3d_context *context;

    context = context_acquire(cs->device, NULL, 0);
    if (context->valid)
        context->gl_info->gl_ops.gl.p_glFlush();
    context_release(context);
}