#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  (* glDeleteFramebuffers ) (int,int /*<<< orphan*/ *) ;} ;
struct wined3d_gl_info {TYPE_1__ fbo_ops; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
typedef  int /*<<< orphan*/  GLuint ;

/* Variables and functions */
 int /*<<< orphan*/  GL_FRAMEBUFFER ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  context_bind_fbo (struct wined3d_context*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  context_clean_fbo_attachments (struct wined3d_gl_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void context_destroy_fbo(struct wined3d_context *context, GLuint fbo)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;

    context_bind_fbo(context, GL_FRAMEBUFFER, fbo);
    context_clean_fbo_attachments(gl_info, GL_FRAMEBUFFER);
    context_bind_fbo(context, GL_FRAMEBUFFER, 0);

    gl_info->fbo_ops.glDeleteFramebuffers(1, &fbo);
    checkGLcall("glDeleteFramebuffers()");
}