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
struct TYPE_6__ {int /*<<< orphan*/  (* p_glDrawBuffer ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_5__ {TYPE_3__ gl; } ;
struct wined3d_gl_info {TYPE_2__ gl_ops; } ;
struct wined3d_context {scalar_t__ draw_buffers_mask; TYPE_1__* current_fbo; struct wined3d_gl_info* gl_info; } ;
struct TYPE_4__ {scalar_t__ rt_mask; } ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  checkGLcall (char*) ; 
 scalar_t__ context_generate_rt_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 

void context_set_draw_buffer(struct wined3d_context *context, GLenum buffer)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    DWORD *current_mask = context->current_fbo ? &context->current_fbo->rt_mask : &context->draw_buffers_mask;
    DWORD new_mask = context_generate_rt_mask(buffer);

    if (new_mask == *current_mask)
        return;

    gl_info->gl_ops.gl.p_glDrawBuffer(buffer);
    checkGLcall("glDrawBuffer()");

    *current_mask = new_mask;
}