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
struct TYPE_6__ {int /*<<< orphan*/  (* glBindFramebuffer ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* glDeleteFramebuffers ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* glFramebufferTexture2D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* glGenFramebuffers ) (int,int /*<<< orphan*/ *) ;} ;
struct TYPE_4__ {int /*<<< orphan*/  (* p_glDeleteTextures ) (int,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* p_glGetTexImage ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ;int /*<<< orphan*/  (* p_glBindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glClear ) (int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glClearColor ) (float,float,float,float) ;int /*<<< orphan*/  (* p_glTexImage2D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* p_glTexParameteri ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glGenTextures ) (int,int /*<<< orphan*/ *) ;} ;
struct TYPE_5__ {TYPE_1__ gl; } ;
struct wined3d_gl_info {TYPE_3__ fbo_ops; TYPE_2__ gl_ops; } ;
struct wined3d_color {float member_0; float member_1; float member_2; float member_3; } ;
struct wined3d_caps_gl_ctx {struct wined3d_gl_info* gl_info; } ;
typedef  int /*<<< orphan*/  GLuint ;
typedef  int DWORD ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
 unsigned int ARRAY_SIZE (int*) ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  GL_BGRA ; 
 int /*<<< orphan*/  GL_COLOR_ATTACHMENT0 ; 
 int /*<<< orphan*/  GL_COLOR_BUFFER_BIT ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_FRAMEBUFFER ; 
 int /*<<< orphan*/  GL_RGBA8 ; 
 int /*<<< orphan*/  GL_TEXTURE_2D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAX_LEVEL ; 
 int /*<<< orphan*/  GL_UNSIGNED_INT_8_8_8_8_REV ; 
 int /*<<< orphan*/  TRACE (char*,int,int,int,int) ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  draw_test_quad (struct wined3d_caps_gl_ctx*,int /*<<< orphan*/ *,struct wined3d_color const*) ; 
 int /*<<< orphan*/  glViewportIndexedf (int /*<<< orphan*/ ,float const,float const,float,float) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub10 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub11 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  stub12 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub13 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub14 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub5 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub8 (float,float,float,float) ; 
 int /*<<< orphan*/  stub9 (int /*<<< orphan*/ ) ; 

BOOL wined3d_caps_gl_ctx_test_viewport_subpixel_bits(struct wined3d_caps_gl_ctx *ctx)
{
    static const struct wined3d_color red = {1.0f, 0.0f, 0.0f, 1.0f};
    const struct wined3d_gl_info *gl_info = ctx->gl_info;
    static const float offset = -63.0f / 128.0f;
    GLuint texture, fbo;
    DWORD readback[4];
    unsigned int i;

    gl_info->gl_ops.gl.p_glGenTextures(1, &texture);
    gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_2D, texture);
    gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, 0);
    gl_info->gl_ops.gl.p_glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, ARRAY_SIZE(readback), 1, 0,
            GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, NULL);
    gl_info->fbo_ops.glGenFramebuffers(1, &fbo);
    gl_info->fbo_ops.glBindFramebuffer(GL_FRAMEBUFFER, fbo);
    gl_info->fbo_ops.glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0,
            GL_TEXTURE_2D, texture, 0);
    checkGLcall("create resources");

    gl_info->gl_ops.gl.p_glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    gl_info->gl_ops.gl.p_glClear(GL_COLOR_BUFFER_BIT);
    GL_EXTCALL(glViewportIndexedf(0, offset, offset, 4.0f, 1.0f));
    draw_test_quad(ctx, NULL, &red);
    checkGLcall("draw");

    gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_2D, texture);
    gl_info->gl_ops.gl.p_glGetTexImage(GL_TEXTURE_2D, 0,
            GL_BGRA, GL_UNSIGNED_INT_8_8_8_8_REV, readback);
    checkGLcall("readback");

    TRACE("Readback colors are 0x%08x, 0x%08x, 0x%08x, 0x%08x.\n",
            readback[0], readback[1], readback[2], readback[3]);

    gl_info->gl_ops.gl.p_glDeleteTextures(1, &texture);
    gl_info->fbo_ops.glDeleteFramebuffers(1, &fbo);
    gl_info->fbo_ops.glBindFramebuffer(GL_FRAMEBUFFER, 0);
    checkGLcall("delete resources");

    for (i = 0; i < ARRAY_SIZE(readback); ++i)
    {
        if (readback[i] != 0xffff0000)
            return FALSE;
    }
    return TRUE;
}