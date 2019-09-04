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
struct TYPE_4__ {int /*<<< orphan*/  (* p_glDisableClientState ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {TYPE_2__ gl; } ;
struct wined3d_gl_info {TYPE_1__ gl_ops; scalar_t__* supported; } ;
struct wined3d_context {scalar_t__ namedArraysLoaded; struct wined3d_gl_info* gl_info; } ;

/* Variables and functions */
 size_t EXT_SECONDARY_COLOR ; 
 scalar_t__ FALSE ; 
 int /*<<< orphan*/  GL_COLOR_ARRAY ; 
 int /*<<< orphan*/  GL_NORMAL_ARRAY ; 
 int /*<<< orphan*/  GL_SECONDARY_COLOR_ARRAY_EXT ; 
 int /*<<< orphan*/  GL_VERTEX_ARRAY ; 
 int /*<<< orphan*/  context_unload_tex_coords (struct wined3d_context*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void context_unload_vertex_data(struct wined3d_context *context)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;

    if (!context->namedArraysLoaded)
        return;
    gl_info->gl_ops.gl.p_glDisableClientState(GL_VERTEX_ARRAY);
    gl_info->gl_ops.gl.p_glDisableClientState(GL_NORMAL_ARRAY);
    gl_info->gl_ops.gl.p_glDisableClientState(GL_COLOR_ARRAY);
    if (gl_info->supported[EXT_SECONDARY_COLOR])
        gl_info->gl_ops.gl.p_glDisableClientState(GL_SECONDARY_COLOR_ARRAY_EXT);
    context_unload_tex_coords(context);
    context->namedArraysLoaded = FALSE;
}