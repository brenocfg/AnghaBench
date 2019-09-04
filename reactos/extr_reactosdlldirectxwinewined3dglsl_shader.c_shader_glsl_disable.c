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
struct wined3d_gl_info {scalar_t__* supported; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; struct glsl_context_data* shader_backend_data; } ;
struct shader_glsl_priv {TYPE_2__* fragment_pipe; TYPE_1__* vertex_pipe; } ;
struct glsl_context_data {int /*<<< orphan*/  vertex_color_clamp; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* enable_extension ) (struct wined3d_gl_info const*,int /*<<< orphan*/ ) ;} ;
struct TYPE_3__ {int /*<<< orphan*/  (* vp_enable ) (struct wined3d_gl_info const*,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 size_t ARB_COLOR_BUFFER_FLOAT ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GL_CLAMP_VERTEX_COLOR_ARB ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FIXED_ONLY_ARB ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glClampColorARB (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glUseProgram (int /*<<< orphan*/ ) ; 
 scalar_t__ needs_legacy_glsl_syntax (struct wined3d_gl_info const*) ; 
 int /*<<< orphan*/  shader_glsl_invalidate_current_program (struct wined3d_context*) ; 
 int /*<<< orphan*/  stub1 (struct wined3d_gl_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (struct wined3d_gl_info const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void shader_glsl_disable(void *shader_priv, struct wined3d_context *context)
{
    struct glsl_context_data *ctx_data = context->shader_backend_data;
    const struct wined3d_gl_info *gl_info = context->gl_info;
    struct shader_glsl_priv *priv = shader_priv;

    shader_glsl_invalidate_current_program(context);
    GL_EXTCALL(glUseProgram(0));
    checkGLcall("glUseProgram");

    priv->vertex_pipe->vp_enable(gl_info, FALSE);
    priv->fragment_pipe->enable_extension(gl_info, FALSE);

    if (needs_legacy_glsl_syntax(gl_info) && gl_info->supported[ARB_COLOR_BUFFER_FLOAT])
    {
        ctx_data->vertex_color_clamp = GL_FIXED_ONLY_ARB;
        GL_EXTCALL(glClampColorARB(GL_CLAMP_VERTEX_COLOR_ARB, GL_FIXED_ONLY_ARB));
        checkGLcall("glClampColorARB");
    }
}