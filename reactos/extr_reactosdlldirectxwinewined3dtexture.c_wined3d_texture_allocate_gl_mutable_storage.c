#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int format_flags; } ;
struct wined3d_texture {unsigned int level_count; scalar_t__ target; unsigned int layer_count; TYPE_1__ resource; } ;
struct TYPE_7__ {int /*<<< orphan*/  (* p_glTexImage2D ) (scalar_t__,unsigned int,scalar_t__,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;int /*<<< orphan*/  (* p_glTexImage1D ) (scalar_t__,unsigned int,scalar_t__,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;} ;
struct TYPE_8__ {TYPE_3__ gl; } ;
struct wined3d_gl_info {TYPE_4__ gl_ops; } ;
struct TYPE_6__ {unsigned int numerator; unsigned int denominator; } ;
struct wined3d_format {int /*<<< orphan*/  glType; int /*<<< orphan*/  glFormat; TYPE_2__ height_scale; } ;
typedef  unsigned int GLsizei ;
typedef  scalar_t__ GLenum ;

/* Variables and functions */
 int /*<<< orphan*/  GL_EXTCALL (int /*<<< orphan*/ ) ; 
 scalar_t__ GL_TEXTURE_1D ; 
 scalar_t__ GL_TEXTURE_1D_ARRAY ; 
 scalar_t__ GL_TEXTURE_2D_ARRAY ; 
 scalar_t__ GL_TEXTURE_3D ; 
 int /*<<< orphan*/  TRACE (char*,struct wined3d_texture*,unsigned int,unsigned int,scalar_t__,unsigned int,unsigned int) ; 
 int WINED3DFMT_FLAG_HEIGHT_SCALE ; 
 int /*<<< orphan*/  checkGLcall (char*) ; 
 int /*<<< orphan*/  glTexImage3D (scalar_t__,unsigned int,scalar_t__,unsigned int,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (scalar_t__,unsigned int,scalar_t__,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (scalar_t__,unsigned int,scalar_t__,unsigned int,unsigned int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 unsigned int wined3d_texture_get_level_depth (struct wined3d_texture*,unsigned int) ; 
 unsigned int wined3d_texture_get_level_pow2_height (struct wined3d_texture*,unsigned int) ; 
 unsigned int wined3d_texture_get_level_pow2_width (struct wined3d_texture*,unsigned int) ; 
 scalar_t__ wined3d_texture_get_sub_resource_target (struct wined3d_texture*,unsigned int) ; 

__attribute__((used)) static void wined3d_texture_allocate_gl_mutable_storage(struct wined3d_texture *texture,
        GLenum gl_internal_format, const struct wined3d_format *format,
        const struct wined3d_gl_info *gl_info)
{
    unsigned int level, level_count, layer, layer_count;
    GLsizei width, height, depth;
    GLenum target;

    level_count = texture->level_count;
    if (texture->target == GL_TEXTURE_1D_ARRAY || texture->target == GL_TEXTURE_2D_ARRAY)
        layer_count = 1;
    else
        layer_count = texture->layer_count;

    for (layer = 0; layer < layer_count; ++layer)
    {
        target = wined3d_texture_get_sub_resource_target(texture, layer * level_count);

        for (level = 0; level < level_count; ++level)
        {
            width = wined3d_texture_get_level_pow2_width(texture, level);
            height = wined3d_texture_get_level_pow2_height(texture, level);
            if (texture->resource.format_flags & WINED3DFMT_FLAG_HEIGHT_SCALE)
            {
                height *= format->height_scale.numerator;
                height /= format->height_scale.denominator;
            }

            TRACE("texture %p, layer %u, level %u, target %#x, width %u, height %u.\n",
                    texture, layer, level, target, width, height);

            if (target == GL_TEXTURE_3D || target == GL_TEXTURE_2D_ARRAY)
            {
                depth = wined3d_texture_get_level_depth(texture, level);
                GL_EXTCALL(glTexImage3D(target, level, gl_internal_format, width, height,
                        target == GL_TEXTURE_2D_ARRAY ? texture->layer_count : depth, 0,
                        format->glFormat, format->glType, NULL));
                checkGLcall("glTexImage3D");
            }
            else if (target == GL_TEXTURE_1D)
            {
                gl_info->gl_ops.gl.p_glTexImage1D(target, level, gl_internal_format,
                        width, 0, format->glFormat, format->glType, NULL);
            }
            else
            {
                gl_info->gl_ops.gl.p_glTexImage2D(target, level, gl_internal_format, width,
                        target == GL_TEXTURE_1D_ARRAY ? texture->layer_count : height, 0,
                        format->glFormat, format->glType, NULL);
                checkGLcall("glTexImage2D");
            }
        }
    }
}