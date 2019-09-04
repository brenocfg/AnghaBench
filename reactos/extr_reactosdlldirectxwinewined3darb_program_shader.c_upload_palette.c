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
struct TYPE_5__ {int /*<<< orphan*/  (* p_glTexImage1D ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ;int /*<<< orphan*/  (* p_glTexParameteri ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glTexEnvi ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glBindTexture ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ;int /*<<< orphan*/  (* p_glGenTextures ) (int,int /*<<< orphan*/ *) ;} ;
struct TYPE_6__ {TYPE_2__ gl; } ;
struct wined3d_gl_info {TYPE_3__ gl_ops; } ;
struct wined3d_context {struct wined3d_gl_info* gl_info; } ;
struct wined3d_arbfp_blitter {int /*<<< orphan*/  palette_texture; } ;
struct TYPE_4__ {struct wined3d_palette* palette; } ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  FIXME (char*) ; 
 int /*<<< orphan*/  GL_BGRA ; 
 int /*<<< orphan*/  GL_CLAMP_TO_EDGE ; 
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GL_NEAREST ; 
 int /*<<< orphan*/  GL_REPLACE ; 
 int /*<<< orphan*/  GL_RGB ; 
 int /*<<< orphan*/  GL_TEXTURE1 ; 
 int /*<<< orphan*/  GL_TEXTURE_1D ; 
 int /*<<< orphan*/  GL_TEXTURE_ENV ; 
 int /*<<< orphan*/  GL_TEXTURE_ENV_MODE ; 
 int /*<<< orphan*/  GL_TEXTURE_MAG_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_MIN_FILTER ; 
 int /*<<< orphan*/  GL_TEXTURE_WRAP_S ; 
 int /*<<< orphan*/  GL_UNSIGNED_INT_8_8_8_8_REV ; 
 int /*<<< orphan*/  context_active_texture (struct wined3d_context*,struct wined3d_gl_info const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  glActiveTexture (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub6 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub7 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 
 int /*<<< orphan*/  stub8 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*) ; 

__attribute__((used)) static void upload_palette(struct wined3d_arbfp_blitter *blitter,
        const struct wined3d_texture *texture, struct wined3d_context *context)
{
    const struct wined3d_palette *palette = texture->swapchain ? texture->swapchain->palette : NULL;
    const struct wined3d_gl_info *gl_info = context->gl_info;

    if (!blitter->palette_texture)
        gl_info->gl_ops.gl.p_glGenTextures(1, &blitter->palette_texture);

    GL_EXTCALL(glActiveTexture(GL_TEXTURE1));
    gl_info->gl_ops.gl.p_glBindTexture(GL_TEXTURE_1D, blitter->palette_texture);

    gl_info->gl_ops.gl.p_glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

    gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    /* Make sure we have discrete color levels. */
    gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    gl_info->gl_ops.gl.p_glTexParameteri(GL_TEXTURE_1D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    /* TODO: avoid unneeded uploads in the future by adding some SFLAG_PALETTE_DIRTY mechanism */
    if (palette)
    {
        gl_info->gl_ops.gl.p_glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 256, 0, GL_BGRA,
                GL_UNSIGNED_INT_8_8_8_8_REV, palette->colors);
    }
    else
    {
        static const DWORD black;
        FIXME("P8 surface loaded without a palette.\n");
        gl_info->gl_ops.gl.p_glTexImage1D(GL_TEXTURE_1D, 0, GL_RGB, 1, 0, GL_BGRA,
                GL_UNSIGNED_INT_8_8_8_8_REV, &black);
    }

    /* Switch back to unit 0 in which the 2D texture will be stored. */
    context_active_texture(context, gl_info, 0);
}