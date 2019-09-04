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
struct TYPE_2__ {int /*<<< orphan*/  (* glFramebufferRenderbuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;} ;
struct wined3d_gl_info {TYPE_1__ fbo_ops; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int /*<<< orphan*/  GLenum ;
typedef  int DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  GL_DEPTH_ATTACHMENT ; 
 int /*<<< orphan*/  GL_RENDERBUFFER ; 
 int /*<<< orphan*/  GL_STENCIL_ATTACHMENT ; 
 int WINED3D_FBO_ENTRY_FLAG_DEPTH ; 
 int WINED3D_FBO_ENTRY_FLAG_STENCIL ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void context_attach_depth_stencil_rb(const struct wined3d_gl_info *gl_info,
        GLenum fbo_target, DWORD flags, GLuint rb)
{
    if (flags & WINED3D_FBO_ENTRY_FLAG_DEPTH)
    {
        gl_info->fbo_ops.glFramebufferRenderbuffer(fbo_target, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rb);
        checkGLcall("glFramebufferRenderbuffer()");
    }

    if (flags & WINED3D_FBO_ENTRY_FLAG_STENCIL)
    {
        gl_info->fbo_ops.glFramebufferRenderbuffer(fbo_target, GL_STENCIL_ATTACHMENT, GL_RENDERBUFFER, rb);
        checkGLcall("glFramebufferRenderbuffer()");
    }
}