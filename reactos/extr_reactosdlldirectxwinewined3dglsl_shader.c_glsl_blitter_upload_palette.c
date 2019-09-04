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
struct wined3d_texture {TYPE_1__* swapchain; } ;
struct wined3d_palette {int /*<<< orphan*/  const* colors; } ;
struct wined3d_glsl_blitter {int /*<<< orphan*/  palette_texture; } ;
struct TYPE_5__ {int /*<<< orphan*/  (* p_glTexImage1D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;int /*<<< orphan*/  (* p_glTexParameteri ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glBindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glGenTextures ) (int,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {TYPE_2__ gl; } ;
struct wined3d_gl_info {TYPE_3__ gl_ops; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct TYPE_4__ {struct wined3d_palette* palette; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GL_BGRA ; 
 int /*<<< orphan*/  GL_CLAMP_TO_EDGE ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_RGB ; 
 int /*<<< orphan*/  GL_TEXTURE_1D ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_UNSIGNED_INT_8_8_8_8_REV ; 
 int /*<<< orphan*/  context_active_texture (struct wined3d_context*,struct wined3d_gl_info const*,int) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void glsl_blitter_upload_palette(struct wined3d_glsl_blitter *blitter,
        struct wined3d_context *context, const struct wined3d_texture *texture)
{
    const struct wined3d_gl_info *gl_info = context->gl_info;
    const struct wined3d_palette *palette;

    palette = texture->swapchain ? texture->swapchain->palette : NULL;

    if (!blitter->palette_texture)
        gl_info->gl_ops.gl.p_glGenTextures(1, &blitter->palette_texture);

    context_active_texture(context, gl_info, 1);
    gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_1D, blitter->palette_texture);
    gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

    if (palette)
    {
        gl_info->gl_ops.gl.p_glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 256, 0, GL_BGRA,
                GL_UNSIGNED_INT_8_8_8_8_REV, palette->colors);
    }
    else
    {
        static const DWORD black;

        FIXME("P8 texture loaded without a palette.\n");
        gl_info->gl_ops.gl.p_glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 1, 0, GL_BGRA,
                GL_UNSIGNED_INT_8_8_8_8_REV, &black);
    }

    context_active_texture(context, gl_info, 0);
}